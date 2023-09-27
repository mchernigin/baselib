ARG DISTR

FROM $DISTR

ARG USER_ID
ARG GROUP_ID

RUN apt-get update \
    && apt-get install -y \
    git \
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

ARG ARCH

RUN echo "#!/bin/sh" > /build.sh \
    && if [ "$ARCH" = "i386" ]; then \
        echo "gear-rpm -ba --target=i386" >> /build.sh; \
    else \
        echo "gear-rpm -ba" >> /build.sh; \
    fi \
    && chmod +x /build.sh

RUN chmod a=rwx,u+t /tmp

USER builder2

RUN chown -R builder2 /app/
WORKDIR /app/

ENTRYPOINT ["/build.sh"]

