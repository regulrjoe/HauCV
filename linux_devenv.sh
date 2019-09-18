docker run -it --rm --mount src=`pwd`,target=/app,type=bind --device=/dev/video0:/dev/video0 gcr.io/hauscv/devenv
