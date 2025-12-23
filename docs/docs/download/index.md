---
hide:
  - navigation
  - toc
---

# Board and Software

HMI SDK provides the following packages:

* **HMI SDK Package**
    *-eSD Boot Image & Toolchain Installer* 

    This package lets you get started right away. You can create a bootable microSD card for the EVK, set up the Linux environment, run the prebuilt demo applications, and build sample HMI applications using the included toolchain installer. <br> 
    <br>
    Please go to [Getting Started](../getting_started/) to get started with this HMI SDK Package.

    <br>

* **HMI SDK Yocto Build Package** 
    *-Yocto Recipes & Pre-built Binary for QSPI Boot*

    This package is for when you want more flexibility. You can build and customize the entire HMI SDK from source. You can also try other boot modes such as QSPI or eMMC, in addition to eSD.    

    *  **Source Code** *-Supplementary for HMI SDK Yocto Build Package*  
            Note that this is optional; the supplementary source code used in the Yocto build is provided for offline builds or as a backup if online fetching fails.
    
    <br>
    Please go to [Building the HMI SDK with Yocto](../building_the_hmi_sdk_with_yocto/) to get started with this HMI SDK Yocto Build Package (and Source Code).        

The packages are designed for specific board models, while the source code is universal and can be used across all boards.


{% include "./_components/rz-g2l-evk.md" %}

{% include "./_components/rz-g2lc-evk.md" %}

{% include "./_components/rz-g2ul-evk.md" %}

[Back to Home >](../index.md){ .md-button .md-button--primary .btn-right } [Back to Getting Started >](../getting_started/#step-1-obtain-an-rzg-evk){ .md-button .btn-right #back_to_getting_started_btn }
