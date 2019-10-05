FROM python:3.7

MAINTAINER Jorge V. M. M. <jrgvmm@gmail.com>

# Install dev tools
RUN apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y --no-install-recommends \
	build-essential \
	cmake  \
	git \
	pkg-config \
	unzip \
	vim \
	wget \
	&& apt-get clean -y \
	&& rm -rf /var/lib/apt/lists/*

RUN pip install python-telegram-bot --upgrade \
	&& pip install pymongo==3.9

ENTRYPOINT python /app/app.py
WORKDIR /
