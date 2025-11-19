
FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-22.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \
        cmake \
        wget \
        unzip \
        curl \
        ninja-build \
        build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspaces/Lab5

USER vscode

CMD [ "bash" ]