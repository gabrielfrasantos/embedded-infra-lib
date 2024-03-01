FROM gcr.io/oss-fuzz-base/base-builder@sha256:32fe1a404a72cbdff5b86892a6d2f7e92841ce2812bb1f175a57054cf8f5078e

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
