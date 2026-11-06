#!/usr/bin/env python3

import argparse
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECTS = ROOT / "projects"

print_lock = threading.Lock()


def all_projects():
    return sorted(p.name for p in PROJECTS.iterdir() if p.is_dir() and p.name != "base")


def run(cmd, prefix):
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    for line in proc.stdout:
        with print_lock:
            print(f"[{prefix}] {line}", end="", flush=True)
    return proc.wait() == 0


def build(project):
    image = f"census-{project}"
    return run(["docker", "build", "-t", image, str(PROJECTS / project)], project) and run(
        ["docker", "run", "--rm", "-v", f"{ROOT}:/census", image,
         f"/census/projects/{project}/build.sh"],
        project,
    )


def main():
    parser = argparse.ArgumentParser(description="Build projects with the census plugin.")
    parser.add_argument("projects", nargs="*", help="projects to build (default: all)")
    parser.add_argument("-j", "--jobs", type=int, default=1,
                        help="how many projects to build at once (default: 1, serial)")
    args = parser.parse_args()

    projects = args.projects or all_projects()
    unknown = [p for p in projects if p == "base" or not (PROJECTS / p / "build.sh").is_file()]
    if unknown:
        parser.error(f"unknown project: {', '.join(unknown)}")

    if not run(["docker", "build", "-t", "census-base", str(PROJECTS / "base")], "base"):
        sys.exit(1)

    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = dict(zip(projects, pool.map(build, projects)))

    for project, ok in results.items():
        print(f"{'ok' if ok else 'FAILED'}: {project}")
    sys.exit(0 if all(results.values()) else 1)


if __name__ == "__main__":
    main()
