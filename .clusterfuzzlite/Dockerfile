FROM gcr.io/oss-fuzz-base/base-builder@sha256:c2671782058cad4ef63631c70e554e3c1b68b968206b6c40d9b33e08416d7ef8

HEALTHCHECK NONE

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
