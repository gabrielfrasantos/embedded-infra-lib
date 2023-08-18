FROM gcr.io/oss-fuzz-base/base-builder@sha256:d2a9ace22eef5d9805c82b1c7e46c45ce18a6c4b12eb59d940a40e4936103b6a

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
