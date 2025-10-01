---
hide:
  - navigation
  - toc
---

# Board and Software

HMI SDK provides the following packages:

* eSD boot image and toolchain installer package

    This package is the heart of HMI SDK.
    You can create a bootable microSD card, set up Linux environment on the EVK, and build sample applications.

* Yocto recipe and pre-built binary image package

    This is an optional package.
    If you would like to build the HMI SDK from scratch, or you would like to try QSPI boot or eMMC boot (other than eSD boot mode), get this package.

* Source code package

    When you build the HMI SDK from scratch, you can use source code in this package for offline building.

Except for the source code package, the packages are available for each EVK.

{% include "./_components/rz-g2l-evk.md" %}

{% include "./_components/rz-g2lc-evk.md" %}

{% include "./_components/rz-g2ul-evk.md" %}

[Back to Home >](../index.md){ .md-button .md-button--primary .btn-right } [Back to Getting Started >](../getting_started/index.md#step-1-obtain-an-evaluation-board){ .md-button .btn-right #back_to_getting_started_btn }
