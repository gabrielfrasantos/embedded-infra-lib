FROM gcr.io/oss-fuzz-base/base-builder@sha256:7d17ee3d1a525b82dc566915b81e26986d99681339d623e3766fdae2d700a97f

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
