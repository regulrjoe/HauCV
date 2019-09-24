docker run \
	-it \
	--rm \
	--mount src=`pwd`,target=/app,type=bind \
	--device=/dev/video0:/dev/video0 \
	--device=/dev/snd:/dev/snd \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-e DISPLAY=unix$DISPLAY \
	gcr.io/hauscv/devenv
