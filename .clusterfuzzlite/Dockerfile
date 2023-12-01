FROM gcr.io/oss-fuzz-base/base-builder@sha256:e8550ff2b57077cb14770e2ec5a77bdcd040c602412df65fe7355825f55ed250

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
