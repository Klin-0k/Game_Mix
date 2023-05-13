FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y build-essential cmake
RUN apt-get install -y libgl1-mesa-dev libxrandr-dev
RUN apt-get install -y unzip
COPY . ./TP_2023_Project
WORKDIR ./TP_2023_Project
RUN ./build_linux_version.sh
