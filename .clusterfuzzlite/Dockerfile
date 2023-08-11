FROM gcr.io/oss-fuzz-base/base-builder@sha256:6ebfc3a3524d284c24708d3201b24fff9242a023256fd935fbd3c4fd6deb3fe6

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
