FROM gcr.io/oss-fuzz-base/base-builder@sha256:6d1142db9a9cadd844ea6e3f5a368c1caa394dd0ace3bff1f82fbe6bd273ca56

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
