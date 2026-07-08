FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    qemu-system-x86 \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*
