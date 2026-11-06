FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libgl1-mesa-dev libegl1-mesa-dev libxkbcommon-dev libxkbcommon-x11-dev libfontconfig1-dev \
      libdbus-1-dev libva-dev libdrm-dev libvulkan-dev python3-venv \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/py && /opt/py/bin/pip install --no-cache-dir aqtinstall conan \
    && /opt/py/bin/aqt install-qt linux desktop 6.12.0 linux_gcc_64 -O /opt/Qt

ENV PATH=/opt/py/bin:$PATH

RUN git init $SRC/plotjuggler \
    && git -C $SRC/plotjuggler remote add origin https://github.com/PlotJuggler/PlotJuggler.git \
    && git -C $SRC/plotjuggler fetch --depth 1 origin a8a8a70b7c8019debf5c75f59555067c407a225c \
    && git -C $SRC/plotjuggler checkout FETCH_HEAD \
    && git -C $SRC/plotjuggler submodule update --init --recursive --depth 1

RUN cd $SRC/plotjuggler && conan profile detect \
    && printf 'compiler:\n  clang:\n    version: ["23"]\n' > "$(conan config home)/settings_user.yml" \
    && scripts/configure_conan_remote.sh \
    && conan graph info . -r=plotjuggler-conan -r=conancenter --lockfile=conan.lock --lockfile-partial \
       -s build_type=Release -s compiler.cppstd=20 -c tools.build:download_source=True > /dev/null
