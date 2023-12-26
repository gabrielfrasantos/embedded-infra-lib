FROM gcr.io/oss-fuzz-base/base-builder@sha256:d988d274008af8e0feccced86261a1d7e863e814814f48b31dc5733778061606

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
