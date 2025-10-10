## Updates of VLP/G v3.0.7

HMI SDK v2.3.1.0 uses VLP/G v3.0.7, but some issues were detected in the VLP/G.
VLP/G v3.0.7-update3 was released to address vulnerabilities and improve drivers in VLP/G v3.0.7.

### Changes

Changes in VLP/G v3.0.7-update3 are listed below.

!!! content-wrapper no-indent table-no-sort ""

    | Features                  | Description                   |
    |---------------------------|-------------------------------|
    | Kernel | The VLP/G v3.0.7-update3 includes several minor kernel fixes. |
    | U-Boot | Update vmmc and vqmmc settings for eSD mode. Configure U-Boot to set a random MAC address. |
    | [CVE-2024-53104](https://nvd.nist.gov/vuln/detail/CVE-2024-53104) | Fix out-of-bounds write by skipping UVC_VS_UNDEFINED frame parsing in uvc_parse_format (media: uvcvideo). |
    | [CVE-2025-4802](https://nvd.nist.gov/vuln/detail/CVE-2025-4802) | The VLP/G v3.0.7-update3 includes the patch for the glibc vulnerability. |
    | glib-2.0 | Updated to glib2.0_2.58.3-2+deb10u8. |
    | multimedia | Update runtime dependencies, fix MMNGR issues, and add GRAY10_LE64 support to GStreamer. |
    | attr, binutils, busybox, coreutils, gcc-8, gnupg2, gzip, kbd, libassuan, libgcrypt20, libunistring, nss, openssh, openssl, perl, pkg-config, pseudo, quilt | Switch to the ELTS mirror to prevent removal from the Debian Buster mirror: <br> - attr, coreutils, gcc-8, gnupg2, gzip, kbd, libassuan, libgcrypt20, libunistring, nss, perl, pkg-config, pseudo, quilt <br> Upgraded packages: <br> - binutils 2.31.1-16 -> 2.31.1-16+deb10u1 <br> - busybox 1.30.1-4 -> 1.30.1-4+deb10u1 <br> - openssh 7.9p1-10+deb10u2 -> 7.9p1-10+deb10u5 <br> - openssl 1.1.1n-0+deb10u6 -> 1.1.1n-0+deb10u7 |
    | SSI Driver | Fix random recording failures in full-duplex communication mode (RZ/G2L Series and RZ/G3S). |
    | PCIe Driver | Enables NVMe PCIe support (RZ/G3S only). |

For more detailed information about VLP/G v3.0.7-update3, get [RZ/G Verified Linux Package v3.0.7 (RTK0EF0045Z0021AZJ-v3.0.7-update3)](https://www.renesas.com/en/document/swo/rzg-verified-linux-package-v307-rtk0ef0045z0021azj-v307-update3) and check the release note in the package.

### How to Update VLP/G from v3.0.7 to v3.0.7-update3

To update VLP/G v3.0.7 in HMI SDK v2.3.1.0, build the HMI SDK by following the instructions below.

#### i. First, perform instructions at step 1 and #1 through #4 at step 2 in [How To Build HMI SDK](../../how_to_build_hmi_sdk/).

!!! note "Note"
	You do not need to download the HMI SDK source code package at step 1.
	Due to the update of the VLP/G, source codes of some modules were updated.
	So, you will get new source codes over a network in this build process.

#### ii. Next, replace meta-renesas with new one as follows:

```bash
cd ${WORK}
rm -rf meta-renesas
git clone https://github.com/renesas-rz/meta-renesas.git
cd meta-renesas/
git checkout -b tmp BSP-3.0.7-update3
```
{: .dollar }

#### iii. Then, proceed with #5 through #8 at step 2 in [How To Build HMI SDK](../../how_to_build_hmi_sdk/), but skip #7 at step 2.

!!! note "Note"
	You can skip #7 at step 2 because it shows instructions for offline build using the source code package.

#### iv. Finally, run `#!bash bitbake` command to build images.

=== "RZ/G2L"
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-weston
	```
	{: .dollar }

	!!! note "Note"
		A change of EMMC setting in #9 at [step 2](../../how_to_build_hmi_sdk/#step-2-build-hmi-sdk-source-code) is no longer necessary for VLP/G v3.0.7-update3.

	If you need to create an SDK toolchain, run `#!bash bitbake` command as follows.
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-weston -c populate_sdk
	```
	{: .dollar }

=== "RZ/G2LC"
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-weston
	```
	{: .dollar }

	!!! note "Note"
		A change of SW_SD0_DEV_SEL setting in #9 at [step 2](../../how_to_build_hmi_sdk/#step-2-build-hmi-sdk-source-code) is no longer necessary for VLP/G v3.0.7-update3.

	If you need to create an SDK toolchain, run `#!bash bitbake` command as follows.
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-weston -c populate_sdk
	```
	{: .dollar }

=== "RZ/G2UL"
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-bsp
	```
	{: .dollar }

	If you need to create an SDK toolchain, run `#!bash bitbake` command as follows.
	```bash
	cd ${WORK}/build
	MACHINE=${BOARD} bitbake core-image-bsp -c populate_sdk
	```
	{: .dollar }

After building images or SDK toolchain, you can find them in the following directories, respectively.

* Images: `#!bash ${WORK}/build/tmp/deploy/images/${BOARD}/`
* SDK toolchain: `#!bash ${WORK}/build/tmp/deploy/sdk/`

