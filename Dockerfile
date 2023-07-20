FROM ubuntu:22.04:
RUN apt-get update
RUN apt-get install -y build-essential cmake libgl1-mesa-dev libxrandr-dev libudev-dev libopenal-dev libvorbis-dev libogg-dev libflac-dev libx11-dev libxrandr-dev libxext-dev libxi-dev libxcursor-dev libfreetype6-dev xvfb curl unzip
COPY . app
WORKDIR app
RUN ./build.sh
