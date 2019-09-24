FROM gcr.io/legos-247323/googletest/1.8.x:debian-buster-slim AS gtest
FROM gcr.io/legos-247323/opencv/4.0.x:debian-buster-slim AS opencv
FROM gcr.io/legos-247323/zeromq/4.3.x:debian-buster-slim AS zeromq

FROM gcr.io/legos-247323/base:debian-buster-slim AS builder

MAINTAINER Jorge V. M. M. <jrgvmm@gmail.com>

# Copy lego's dependencies
COPY --from=gtest /opt/ /opt/
COPY --from=opencv /opt/ /opt/
COPY --from=zeromq /opt/ /opt/

# Install dev tools
RUN apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y --no-install-recommends \
	build-essential \
	gdb \
	mpg123 \
	libssl-dev \
	libffi-dev \
	python-dev \
	python3-pip \
	vim \
	&& apt-get clean -y \
	&& rm -rf /var/lib/apt/lists/*

# Install dbg-macro
RUN git clone https://github.com/sharkdp/dbg-macro /dbg-macro \
	&& ln -s $(readlink -f dbg-macro/dbg.h) /usr/include/dbg.h

WORKDIR /
