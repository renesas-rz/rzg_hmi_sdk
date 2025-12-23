## Introduction

This page guides you through building the HMI SDK with Yocto. You will be able to modify the source code and customize the Linux environment according to your needs.

To build Yocto Linux, the following equipment should be prepared.


!!! content-wrapper no-indent table-no-sort table-no-hover ""
    +-----------+------------------------------------------------------+
    | Equipment | Details                                              |
    +===========+======================================================+
    | Linux PC  | Approximately the following free space is required.  |
    |           | - **150 GB for RZ/G2L EVK**                          |
    |           | - **150 GB for RZ/G2LC EVK**                         |
    |           | - **85 GB for RZ/G2UL EVK**                          |
    |           +------+-----------------------------------------------+
    |           | OS   | **Ubuntu 22.04 LTS, 64-bit version**          |
    |           |      |                                               |
    +-----------+------+-----------------------------------------------+

!!! warning "Notice"
    Several updated OSS components, released to address security vulnerabilities and enhance driver performance, are now available on Renesas' GitHub. Please refer to [How to Update Linux Packages in the HMI SDK](../wiki/common_update-linux-package/) for instructions on how to replace them.
