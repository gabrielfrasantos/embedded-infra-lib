FROM gcr.io/oss-fuzz-base/base-builder@sha256:0e9d38992a39eb5198acf920897d48579a1086302d2671508d312346fd9a9e4e

HEALTHCHECK NONE

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
