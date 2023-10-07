FROM gcr.io/oss-fuzz-base/base-builder@sha256:3de955226ea5b19edddd2c897ef93aef1c481f17091ad1c25c32d3bea9f4d5dc

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
