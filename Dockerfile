ARG DISTR

# Container image that runs your code
FROM $DISTR

ARG USER_ID
ARG GROUP_ID

RUN apt-get update \
    && apt-get install -y git \
    gear \
    hasher \
    hasher-priv \
    hasher-rich-chroot \
    hasher-rich-chroot-user-utils \
    rpm-utils \
    rpm-build \
    rpm-build-licenses \
    rpm-macros-cmake \
    rpm-macros-make \
    rpm-macros-generic-compat \
    apt-repo \
    apt-repo-tools \
    cmake \
    rpm-macros-cmake \
    cmake-modules \
    gcc-c++ \
    qt5-base-devel \
    qt5-declarative-devel \
    qt5-tools-devel \
    libsmbclient-devel \
    libsmbclient \
    qt5-base-common \
    doxygen \
    xorg-xvfb \
    xvfb-run \
    sudo \
    && export CURRENT_PWD=`pwd` \
    && if [ $(getent group $GROUP_ID) ]; then \
      echo "group $GROUP_ID exists."; \
    else \
      groupadd --gid $GROUP_ID builder2; \
    fi \
    && useradd --uid $USER_ID --gid $GROUP_ID -ms /bin/bash builder2 \
    && groupadd sudo \
    && usermod -aG rpm builder2 \
    && usermod -aG sudo root \
    && usermod -aG sudo builder2 \
    && echo "root ALL=(ALL) NOPASSWD:ALL" | tee -a /etc/sudoers \
    && echo "builder2 ALL=(ALL) NOPASSWD:ALL" | tee -a /etc/sudoers \
    && hasher-useradd builder2 || : \
    && mkdir /app \
    && chown $USER_ID:$GROUP_ID /app

# Copies your code file from your action repository to the filesystem path `/` of the container
# COPY script/build.sh /build.sh

RUN echo -e "#!/bin/sh -ex\nexport TMPDIR=/home/builder2/tmp\nchown -R builder2 /app/\ncd /app/ && gear-rpm -ba" \
         > /build.sh \
    && chmod +x ./build.sh

ARG ARCH

RUN if [ "$ARCH" = "i386" ]; then \
        sed -i 's/gear-rpm -ba/gear-rpm -ba --target=i386/g' build.sh; \
    fi

USER builder2
WORKDIR /home/builder2

RUN mkdir tmp

# Code file to execute when the docker container starts up (`build.sh`)
ENTRYPOINT ["/build.sh"]
