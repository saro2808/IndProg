FROM ubuntu:18.04

RUN apt-get update && apt-get install -y vim

RUN apt-get install -y apt-utils

RUN apt-get install -y g++

RUN apt-get install -y git

RUN apt install -y libprotobuf-dev protobuf-compiler

RUN apt-get -y install cmake

ADD /picture-vr /picture-vr

WORKDIR /picture-vr/source/imitator

CMD ["./run.sh"]
