#!/usr/bin/env python3

import argparse
import logging
import os
import shlex
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECTS = ROOT / "projects"
PLUGIN = "/census/build/plugin/census.so"

log = logging.getLogger("census")
print_lock = threading.Lock()


def all_projects():
    return sorted(p.name for p in PROJECTS.iterdir() if p.is_dir() and p.name != "base")


def run(cmd, prefix):
    log.info("[%s] $ %s", prefix, shlex.join(cmd))
    start = time.monotonic()
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    for line in proc.stdout:
        with print_lock:
            print(f"[{prefix}] {line}", end="", flush=True)
    code = proc.wait()
    elapsed = time.monotonic() - start
    if code == 0:
        log.info("[%s] finished in %.1fs", prefix, elapsed)
    else:
        log.error("[%s] failed with exit code %d after %.1fs", prefix, code, elapsed)
    return code == 0


def in_base(script):
    return ["docker", "run", "--rm", "--user", f"{os.getuid()}:{os.getgid()}",
            "-v", f"{ROOT}:/census", "census-base", "bash", "-c", script]


def build(project, cxxflags):
    log.info("[%s] starting", project)
    start = time.monotonic()
    image = f"census-{project}"
    ok = run(["docker", "build", "-t", image, str(PROJECTS / project)], project) and run(
        ["docker", "run", "--rm", "-v", f"{ROOT}:/census", "-e", f"CXXFLAGS={cxxflags}",
         image, f"/census/projects/{project}/build.sh"],
        project,
    )
    elapsed = time.monotonic() - start
    if ok:
        log.info("[%s] ok in %.1fs", project, elapsed)
    else:
        log.error("[%s] FAILED after %.1fs", project, elapsed)
    return ok, elapsed


def main():
    parser = argparse.ArgumentParser(description="Build projects with the census plugin.")
    parser.add_argument("projects", nargs="*", help="projects to build (default: all)")
    parser.add_argument("-j", "--jobs", type=int, default=1,
                        help="how many projects to build at once (default: 1, serial)")
    parser.add_argument("-f", "--filters", nargs="?", const="",
                        help="comma-separated filters to run (default: all); "
                             "without a value, list the supported filters")
    args = parser.parse_args()

    logging.basicConfig(
        stream=sys.stdout,
        level=logging.INFO,
        format="%(asctime)s %(levelname)-5s %(message)s",
        datefmt="%H:%M:%S",
    )

    projects = args.projects or all_projects()
    unknown = [p for p in projects if p == "base" or not (PROJECTS / p / "build.sh").is_file()]
    if unknown:
        parser.error(f"unknown project: {', '.join(unknown)}")

    start = time.monotonic()

    if not run(["docker", "build", "-t", "census-base", str(PROJECTS / "base")], "base"):
        log.error("base image failed, not building any project")
        sys.exit(1)

    if not run(in_base("cmake -S /census/src -B /census/build/plugin -G Ninja"
                       " && cmake --build /census/build/plugin"), "plugin"):
        log.error("plugin failed, not building any project")
        sys.exit(1)

    if args.filters == "":
        names = subprocess.run(
            in_base(f"echo | $CXX -x c++ -fsyntax-only -fplugin={PLUGIN} -fplugin-arg-census-list -"),
            check=True, capture_output=True, text=True).stdout.split()
        print("\n".join(sorted(names)))
        sys.exit(0)

    log.info("building %d project(s), %d at a time: %s", len(projects), args.jobs, " ".join(projects))

    cxxflags = f"-fplugin={PLUGIN}"
    if args.filters is not None:
        for name in args.filters.split(","):
            cxxflags += f" -fplugin-arg-census-{name}"
    log.info("filters: %s", args.filters or "all")

    if not run(in_base(f"echo | $CXX -x c++ -fsyntax-only {cxxflags} -"), "plugin"):
        log.error("plugin does not load with these filters, not building any project")
        sys.exit(1)

    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = dict(zip(projects, pool.map(lambda p: build(p, cxxflags), projects)))

    run(in_base("find /census/src -name '*.cpp' -o -name '*.h'"
                " | xargs clang-format-$CLANG_VERSION -i"), "format")

    failed = [p for p, (ok, _) in results.items() if not ok]
    log.info("summary:")
    for project, (ok, elapsed) in results.items():
        log.info("  %-6s %-20s %7.1fs", "ok" if ok else "FAILED", project, elapsed)
    log.info("%d ok, %d failed, total %.1fs", len(projects) - len(failed), len(failed),
             time.monotonic() - start)
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
