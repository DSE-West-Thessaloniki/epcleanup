# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.205.2/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends cmake qtbase5-dev qt5-qmake

RUN echo "deb http://pkg.mxe.cc/repos/apt focal main" >/etc/apt/sources.list.d/mxeapt.list

RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 86B72ED9

RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y mxe-i686-w64-mingw32.shared-qt5

ENV PATH=/usr/lib/mxe/usr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

RUN apt-get clean && rm -Rf /var/lib/apt/lists/*

CMD ["/bin/bash"]