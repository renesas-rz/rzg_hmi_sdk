## Step 2: Build HMI SDK source code

This step explains how to build Linux environment with HMI SDK source code.

!!! note
    In the following instructions, text in angle brackets should be replaced
    with a character string that depends on your environment.

    The brackets `<` and `>` are unnecessary in the text.


1.  Install the required packages

    Install some packages into your Linux PC, which are necessary in the following steps.

    ```bash
    sudo apt-get update
    sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libsdl1.2-dev xterm p7zip-full libyaml-dev libssl-dev bmap-tools

    ```
    {: .dollar }

2.  Set up your `#!bash git` environment

    Set up your `#!bash git` environment if you have never done it.

    ```bash
    git config --global user.email "<Your email address>"
    git config --global user.name "<Your user name>"
    ```
    {: .dollar }

    !!! note
        For more information, refer to [Yocto Project Quick Build](https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html){: target=_blank }.

3.  Set environment variables

    Set the following environment variables.

    === "RZ/G2L"

        ```bash
        export WORK=<A directory path for building>
        export PLATFORM=rzg2l
        export BOARD=smarc-rzg2l
        export SDK_PKG_DIR=<A directory path for HMI SDK source code packages>
        ```
        {: .dollar }

        !!! note
            Currently, RZ/G Linux HMI SDK supports only `#!bash rzg2l` for
            `#!bash PLATFORM` and `#!bash smarc-rzg2l` for `#!bash BOARD`.

            The directory set to `#!bash SDK_PKG_DIR` shall include the HMI SDK
            source code package such as `#!bash RTK0EF0195F*SJ_linux-src.zip`.

4.  Extract Yocto recipe package

    Decompress the source code package, create a working directory, and
    extract Yocto recipe package.

    === "RZ/G2L"

        ```bash
        cd ${SDK_PKG_DIR}
        unzip RTK0EF0195F*SJ_linux-src.zip
        ```
        {: .dollar }

        ```bash
        mkdir -p ${WORK}
        cd ${WORK}
        tar xf ${SDK_PKG_DIR}/RTK0EF0195F*SJ_linux-src/yocto_recipe_rzg2l_hmi-sdk_v*.tar.gz --strip-components 1

        ```
        {: .dollar }

5.  Initialize build environment

    Run an environment setup script as follows.

    ```bash
    cd ${WORK}
    TEMPLATECONF=${PWD}/meta-renesas/meta-${PLATFORM}/docs/template/conf/ source poky/oe-init-build-env build
    ```
    {: .dollar }

6.  Add layers

    Add necessary Yocto `#!bash meta-layers` layer as follows.

    ```bash
    cd ${WORK}/build
    bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics
    bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs
    bitbake-layers add-layer ../meta-rz-demos
    ```
    {: .dollar }

7.  Set up environment for offline build

    This step is configuration for offline building.

    If you would like to get source code via network when you build the HMI
    SDK, skip this step.

    Change the environment variable `#!bash BB_NO_NETWORK` in
    `#!bash local.conf` from `#!bash 0`  to `#!bash 1` using `#!bash sed`
    command.

    ```bash
    cd ${WORK}/build
    sed -i "s|\(BB_NO_NETWORK =.*\)\"0\"|\1\"1\"|" "conf/local.conf"
    ```
    {: .dollar }

    Decompress OSS source code package and set it into the build
    environment.

    === "RZ/G2L"

        ```bash
        cd ${SDK_PKG_DIR}/RTK0EF0195F*SJ_linux-src/
        7z x oss-souce-code-pkg_rzg2l_hmi-sdk_v*.7z
        mv oss-souce-code-pkg_rzg2l_hmi-sdk_v*/downloads/ ${WORK}/build/
        ```
        {: .dollar }

8.  Modify configurations for build environment

    Add `#!bash IMAGE_INSTALL_append` and `#!bash WHITELIST_GPL-3.0` to
    `#!bash local.conf` as follows.

    ```bash
    cd ${WORK}/build
    sed -i '$aIMAGE_INSTALL_append = \" packagegroup-lvgl-demo packagegroup-benchmark-tools packagegroup-rz-benchmark-demo\"' "conf/local.conf"
    sed -i '$aWHITELIST_GPL-3.0 += \" glmark2 \"' "conf/local.conf"
	```
    {: .dollar }

9.  Build images

    Run `#!bash bitbake` command to build images.

    ```bash
    cd ${WORK}/build
    MACHINE=${BOARD} bitbake core-image-weston
    ```
    {: .dollar }

    !!! note
        If you need to create an SDK toolchain, run `#!bash bitbake`
        command as follows.

    	```bash
    	cd ${WORK}/build
    	MACHINE=${BOARD} bitbake core-image-weston -c populate_sdk
    	```
        {: .dollar }

    !!! note
    	After building images or SDK toolchain, you can find them in the
        following directories respectively.

    	* Images: `#!bash ${WORK}/build/tmp/deploy/images/${BOARD}/`
    	* SDK toolchain: `#!bash ${WORK}/build/tmp/deploy/sdk/`
