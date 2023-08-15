FROM gcr.io/oss-fuzz-base/base-builder@sha256:af71bd4fe5ac8e56060953af36b6567682a1543412b881db01b458e193b4e507

RUN apt-get update && apt-get upgrade -y --no-install-recommends \
        ninja-build \
 && rm -rf /var/lib/apt/lists/*

COPY . $SRC/amp-embedded-infra-lib
COPY .clusterfuzzlite/build.sh $SRC/

WORKDIR $SRC/amp-embedded-infra-lib
