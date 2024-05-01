FROM gcr.io/oss-fuzz-base/base-builder@sha256:5d9a51721b560306150353651a6dc85ce0cb6c8c2892fc9846de70c08b58f1e7

HEALTHCHECK NONE

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
