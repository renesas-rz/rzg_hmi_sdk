## Step 2: Build HMI SDK with Yocto

!!! success "Tip"
    In the following instructions, text shown in angle brackets should be replaced with values specific to your environment. <br>
    The angle brackets `<` and `>` should not be included when you enter the text.

1.  Install the required packages.

    Run the following command to install the required packages on your Linux PC.

    ```bash
    sudo apt-get update
    sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libsdl1.2-dev xterm p7zip-full libyaml-dev libssl-dev bmap-tools file git libacl1 liblz4-tool locales python3-git python3-jinja2 python3-subunit zstd

    ```
    {: .dollar }

2.  Set up the `#!bash git` environment.

    Run the following command to set up the `git` environment if it has not been configured yet.

    ```bash
    git config --global user.email "<Your email address>"
    git config --global user.name "<Your user name>"
    ```
    {: .dollar }

    !!! note
        For more information, refer to [Yocto Project Quick Build](https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html){: target=_blank }.

3.  Set environment variables.

    Please set the following environment variables.

    === "RZ/G3E"

        ```bash
        export WORK=<A directory path for building>
        export PLATFORM=rzg3e
        export BOARD=smarc-rzg3e
        export SDK_PKG_DIR=<A directory path for HMI SDK Yocto Build packages>
        ```
        {: .dollar }

    !!! success "Tip"
        The `#!bash SDK_PKG_DIR` should point to the directory where you have downloaded your HMI SDK Yocto Build Packages, including `#!bash RTK0EF0195F*SJ_${PLATFORM}_yocto-and-pre-built-image.zip` and `#!bash RTK0EF0195F*SJ_linux-src.zip`.

4.  Extract the Yocto recipe package.

    Decompress the Yocto recipe and pre-built binary image packages.

    ```bash
    cd ${SDK_PKG_DIR}
    unzip RTK0EF0195F*SJ_${PLATFORM}_yocto-and-pre-built-image.zip
    ```
    {: .dollar }

    Create a working directory.

    ```bash
    mkdir -p ${WORK}
    ```
    {: .dollar }

    Extract the Yocto recipe package.

    ```bash
    cd ${WORK}
    tar xf ${SDK_PKG_DIR}/RTK0EF0195F*SJ_${PLATFORM}_yocto-and-pre-built-image/yocto_recipe_${PLATFORM}_hmi-sdk_v*.tar.gz --strip-components 1
    ```
    {: .dollar }

5.  Initialize the build environment.

    Run the given environment setup script with the command shown below.

    ```bash
    cd ${WORK}
    TEMPLATECONF=${PWD}/meta-renesas/meta-rz-distro/conf/templates/rz-conf/ source poky/oe-init-build-env build
    ```
    {: .dollar }

6.  Add layers.

    Add necessary Yocto `#!bash meta-layers` using the following commands.

    === "RZ/G3E"

        ```bash
        cd ${WORK}/build
        bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics
        bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs
        bitbake-layers add-layer ../meta-clang
        bitbake-layers add-layer ../meta-lts-mixins
        bitbake-layers add-layer ../meta-browser/meta-chromium
        bitbake-layers add-layer ../meta-openembedded/meta-networking
        bitbake-layers add-layer ../meta-browser-hwdecode
        bitbake-layers add-layer ../meta-rz-features/meta-rz-flutter
        bitbake-layers add-layer ../meta-rz-features/meta-rz-flutter-demo
        bitbake-layers add-layer ../meta-flutter
        bitbake-layers add-layer ../meta-flutter/meta-flutter-apps
        bitbake-layers add-layer ../meta-rz-demos
        ```
        {: .dollar }


7.  Set up the environment for an offline build.

    !!! warning "Notice"
        This step configures the environment for offline building when you choose to download the **Source Code** manually.

        If you prefer to obtain the source code via the network while building the HMI SDK with Yocto, you can skip this <span style="color: var(--renesas-secondary-color-fg-blue-teal")>*Step 2-7*</span> and continue directly with <span style="color: var(--renesas-secondary-color-fg-blue-teal")>*Step 2-8*</span>.

    Change the environment variable `#!bash BB_NO_NETWORK` in `#!bash local.conf` from `#!bash 0`  to `#!bash 1` using the `#!bash sed` command.

    ```bash
    cd ${WORK}/build
    sed -i '$aBB_NO_NETWORK = "1"' "conf/local.conf"
    ```
    {: .dollar }

    Decompress the downloaded **Source Code** and set it up in the build environment.

    ```bash
    cd ${SDK_PKG_DIR}
    unzip RTK0EF0195F*SJ_linux-src.zip
    cd ${SDK_PKG_DIR}/RTK0EF0195F*SJ_linux-src/
    7z x oss-souce-code-pkg_${PLATFORM}_hmi-sdk_v*.7z
    mv downloads/ ${WORK}/build/
    ```
    {: .dollar }

8.  Modify the configurations for the build environment.

    Add `#!bash IMAGE_INSTALL_append` and other settings to `#!bash local.conf` using the command shown below.

    === "RZ/G3E"

        ```bash
        cd ${WORK}/build
        sed -i '$aIMAGE_INSTALL:append = \" packagegroup-lvgl-demo packagegroup-benchmark-tools packagegroup-chromium-demo packagegroup-rzg-hmi-sdk-demo \"' "conf/local.conf"
        ```
        {: .dollar }

9.  Build images.

    Run the `#!bash bitbake` command to build the images.

    === "RZ/G3E"

        ```bash
        cd ${WORK}/build
        MACHINE=${BOARD} bitbake core-image-weston
        ```
        {: .dollar }

    !!! success "Tip"
        The build may take several hours, depending on the PC specifications.  
    
    This completes the build of the Linux environment.  

10. Create the SDK toolchain.

    If you want to further deploy sample or your customized applications, building the `toolchain` is also required. Create the SDK toolchain using the following command.

    === "RZ/G3E"

        ```bash
        cd ${WORK}/build
        MACHINE=${BOARD} bitbake core-image-weston -c populate_sdk
        ```
        {: .dollar }

This concludes the Building the HMI SDK with Yocto guide.  

!!! success "Tip"
    Your newly built images and SDK toolchain will be generated in the following directories.  
        **Images**: `#!bash ${WORK}/build/tmp/deploy/images/${BOARD}/`  
        **SDK toolchain**: `#!bash ${WORK}/build/tmp/deploy/sdk/`

To flash the image to the SD card using bmaptool, refer to [Step 4: Create SD Cards with the Prebuilt Image](../getting_started/#step-4-create-sd-cards-with-the-prebuilt-image).



To boot your device using the prepared SD card, refer to [EVK DIP Switch Setup](../hmi_applications/#evk-dip-switch-setup) for your boot mode setup.
<br><br>
For detailed information about each demo application, see [Demo Applications](../hmi_applications/#demo-applications).<br>
For further development of sample applications, see [Sample Applications](../hmi_applications/#sample-applications).<br>
For additional customizations, see [Wiki](../wiki/).
