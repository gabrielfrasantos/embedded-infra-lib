FROM gcr.io/oss-fuzz-base/base-builder@sha256:b67b62e9be63fa7017f477049359bd5ee53c73afcd826a3cdfa3f45d7021d031

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
