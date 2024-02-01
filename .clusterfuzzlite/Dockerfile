FROM gcr.io/oss-fuzz-base/base-builder@sha256:5f9cc22c96bb55fe00ec9aa1b084c37f4fd24b1ddfabf0ae95955fe8ed02c790

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
