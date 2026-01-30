## Step 4: Create SD Cards with the Prebuilt Image

=== "RZ/G3E"

    After downloading the HMI SDK Package, locate the image file.


    !!! content-wrapper no-indent table-no-sort table-no-hover ""

        +------------+---------------------------------------+-----------------------------------------+
        |Target Board|Image File                             |Location                                 |
        +============+=======================================+=========================================+
        | RZ/G3E     |*core-image-weston-smarc-rzg3e.wic.gz* |*image-file_rzg3e_hmi-sdk_ve.4.0.0.zip*  |
        +------------+---------------------------------------+-----------------------------------------+
    

    #### Option 1. For Windows PC

    1.  Download or copy the HMI SDK package to your PC.
    2.  Unzip the package and extract the image file.

        *i.* Right-click the downloaded package `RTK0EF0195F03400SJ_rzg3e.zip` → Extract All...<br>
        *ii.* Open the folder and right-click `image-file_rzg3e_hmi-sdk_v3.4.0.0.zip` → Extract All...<br> 
        *iii.* Inside, you will find the image file: `core-image-weston-smarc-rzg3e.rootfs.wic.gz`

    3.  Flash the image file `core-image-weston-smarc-rzg3e.rootfs.wic.gz` to your micro SD card using one of the following tools:
        *   [Win32 Disk Imager](https://sourceforge.net/projects/win32diskimager/){: target=_blank }
        *   [balenaEtcher](https://etcher.balena.io/){: target=_blank }


        !!! danger "Caution"
            Even if you see a message such as `you need to format the disk` before/after flashing the image, do not format the SD card.

    #### Option 2. For Linux PC (Ubuntu)

    1.  Install the required packages and software.

        *i.* Run the following command to install the required packages.

        ```bash
        sudo apt-get update
        sudo apt-get install unzip bmap-tools
        ```
        {: .dollar }

        
        *ii.* Run the following command to set up the `git` environment if it has not been configured yet.

        !!! success "Tip"
            This step is required only if you plan to continue with further development, such as building sample applications. If you only want to complete [Step 5: Run the HMI Demo Applications](#step-5-run-the-hmi-demo-applications), you may skip this step.

        ```bash
        git config --global user.email "<Your email address>"
        git config --global user.name "<Your user name>"
        ```
        {: .dollar }

        !!! note
            For more information, refer to [Yocto Project Quick Build](https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html){: target=_blank }.

        
    2.  Download or copy the HMI SDK package to your PC.
    3.  Unzip the package and extract the image file.

        !!! success "Tip"
            If you are using the GUI of Linux Ubuntu, please refer to the similar steps described in the [Option 1. For Windows PC -2](../getting_started/#option-1-for-windows-pc).
        
        *i.* Unzip the HMI SDK package.

        Navigate to the directory where the HMI SDK package was installed.

        ```bash
        unzip RTK0EF0195F03400SJ_rzg3e.zip
        cd RTK0EF0195F03400SJ_rzg3e/
        ```
        {: .dollar }

        *ii.* Unzip the image file folder.

        ```bash
        unzip image-file_rzg3e_hmi-sdk_v3.4.0.0.zip
        cd image-file_rzg3e_hmi-sdk_v3.4.0.0/
        ```
        {: .dollar }

        *iii.* Locate the target image file `#!bash core-image-weston-smarc-rzg3e.rootfs.wic.gz`.

        ```bash
        ls
        ```
        {: .dollar }


        ```bash
        core-image-weston-smarc-rzg3e.rootfs.wic.gz
        core-image-weston-smarc-rzg3e.rootfs.wic.bmap
        core-image-weston-smarc-rzg3e.rootfs.manifest
        ```
        
        !!! warning "Notice"
            *  No need to decompress `core-image-weston-smarc-rzg3e.rootfs.wic.gz` manually.
            *  Ensure that the image file `core-image-weston-smarc-rzg3e.rootfs.wic.gz` is located in the **same directory** as `core-image-weston-smarc-rzg3e.rootfs.wic.bmap` to flash the image to the SD card successfully.
            
    4. Insert the micro SD card into your Linux PC and identify its device name and mount points.

        Use the `lsblk` command to check the `<device name>` and `<mount point>` as follows:

        *   Before inserting the SD card:

            ```bash
            lsblk
            ```
            {: .dollar }

            ```bash
            NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
                (snip)
            nvme0n1     259:0    0 465.8G  0 disk
            ├─nvme0n1p1 259:1    0   512M  0 part /boot/efi
            └─nvme0n1p2 259:2    0 465.3G  0 part /
            ```

            *   After inserting the SD card:

            ```bash
            lsblk
            ```
            {: .dollar }

            ```bash
            NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
                (snip)
            nvme0n1     259:0    0 465.8G  0 disk
            ├─nvme0n1p1 259:1    0   512M  0 part /boot/efi
            └─nvme0n1p2 259:2    0 465.3G  0 part /
            sda           8:0    1  14.5G  0 disk
            ├─sda1        8:1    1   500M  0 part /media/user/boot
            └─sda2        8:2    1   3.4G  0 part /media/user/rootfs
            ```

        !!! success "Tip"
            The device name is assigned to the SD card by Linux on your Host PC.
            It typically appears as `#!bash /dev/sdx`, where `#!bash x` is a letter representing the physical drive.
            In this example, the SD card’s device name is `#!bash /dev/sda`, and its mount points are `#!bash /media/user/boot` and `#!bash /media/user/rootfs`

    5.  Unmount the SD card if it is currently mounted.

        Use the `umount` command with the mount points. 
        
        ```bash
        umount <mount point>
        ```
        {: .dollar }

        In this example:

        ```bash
        umount /media/user/boot
        umount /media/user/rootfs
        ```
        {: .dollar }

    6.  Flash the image to the SD card using `bmaptool`.

        Use the `bmaptool` command with the device name of SD card. 

        !!! danger "Caution"
            Before running `bmaptool`, double-check the `<device name>`. Make sure the target device (your SD card) is correct and **not your system disk**. Using the wrong device will overwrite all data on that disk and may render your system unbootable.

        !!! danger "Caution"
            The operation below **will erase** the contents of your SD card.        
        
        ```bash
        sudo bmaptool copy core-image-weston-smarc-rzg3e.rootfs.wic.gz <device name>
        ```
        {: .dollar }
        
        In this example:

        ```bash
        sudo bmaptool copy core-image-weston-smarc-rzg3e.rootfs.wic.gz /dev/sda
        ```
        {: .dollar }

