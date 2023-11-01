FROM gcr.io/oss-fuzz-base/base-builder@sha256:92183ea7348e64e7ca525cd3561b252211469431e217e672d39cc474b3d78645

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
