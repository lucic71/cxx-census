FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      librsvg2-dev libgtk-3-dev libpoppler-glib-dev portaudio19-dev libsndfile1-dev liblua5.4-dev \
      libzip-dev gettext help2man libgtksourceview-4-dev libqpdf-dev libxml2-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/xournalpp \
    && git -C $SRC/xournalpp remote add origin https://github.com/xournalpp/xournalpp.git \
    && git -C $SRC/xournalpp fetch --depth 1 origin e6029a5d0335534d54539e03bcf184dc00ebccef \
    && git -C $SRC/xournalpp checkout FETCH_HEAD
