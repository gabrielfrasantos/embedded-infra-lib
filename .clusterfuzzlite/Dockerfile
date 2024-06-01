FROM gcr.io/oss-fuzz-base/base-builder@sha256:9fe303bb55cb3cf08b3f291f8f644348f99f0093ba2c460f948061b494ecc31b

HEALTHCHECK NONE

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
