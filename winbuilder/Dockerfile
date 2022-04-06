FROM ubuntu:focal

RUN apt-get update && \
	DEBIAN_FRONTEND=noninteractive \
	apt-get install -y --no-install-recommends \
		software-properties-common \
		lsb-release \
		ca-certificates \
		build-essential \
		gnupg \
		# dependencies for epcleanup
		qtbase5-dev

RUN apt-key adv \
		--keyserver keyserver.ubuntu.com \
		--recv-keys 86B72ED9 && \
	add-apt-repository \
    	"deb [arch=amd64] https://pkg.mxe.cc/repos/apt `lsb_release -sc` main" && \
	apt-get update && \
	DEBIAN_FRONTEND=noninteractive \
	apt-get install -y --no-install-recommends \
		mxe-i686-w64-mingw32.static-cc \
		mxe-i686-w64-mingw32.static-qt5

COPY ./mxebuild.sh /build/

RUN chmod +x /build/mxebuild.sh

CMD ["/build/mxebuild.sh"]