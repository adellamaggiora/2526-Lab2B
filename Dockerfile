FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Aggiornamento e installazione pacchetti
RUN apt-get update && apt-get install -y \
    gcc \
    gcc-doc \
    make \
    make-doc \
    geany \
    valgrind \
    gdb \
    manpages-posix \
    build-essential \
    man-db \
    vim \
    nano \
    && apt-get clean

# Cartella di lavoro
WORKDIR /workspace

# Shell di default
CMD ["/bin/bash"]