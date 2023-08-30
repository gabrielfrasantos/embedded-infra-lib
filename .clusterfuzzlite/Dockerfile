FROM gcr.io/oss-fuzz-base/base-builder@sha256:8e70c5f63e530f520afaaa712360a732d4424a41cd0e3aea288e4be9ea80ac9f

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
