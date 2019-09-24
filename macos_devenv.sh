docker run \
	-it \
	--rm \
	--mount src=`pwd`,target=/app,type=bind \
	--device=/dev/snd:/dev/snd \
	gcr.io/hauscv/devenv
