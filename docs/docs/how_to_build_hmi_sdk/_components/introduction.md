## Introduction

HMI SDK is a quick and easy HMI Application development environment.

To modify Linux component, you need to build HMI SDK from source code.
HMI SDK source code will generate same Linux environment as HMI SDK.

This page explains how to build HMI SDK source code.
After you have completed this page, you would be able to change the source code and customize Linux environment (i.e., memory map, additional OSS etc...).

!!! failure "Notice"
	Several updated OSS components, aimed at addressing vulnerabilities and improving drivers, have been published on Renesas' GitHub.
	Please refer to [Update Linux Package in HMI SDK](../wiki/common_update-linux-package/) for instructions on how to replace them.

!!! note "Requirement"
    1.  Users have launched Evaluation Board Kit according to [Getting Started](../getting_started/index.md),
        which means they can run HMI Application on the board.
    2.  To build Yocto Linux, the below equipment should be prepared.

        !!! content-wrapper no-indent table-no-sort table-no-hover ""

            +-----------+------------------------------------------------------+
            | Equipment | Details                                              |
            +===========+======================================================+
            | Linux PC  | Approximately the following free space is necessary. |
            |           | - **150 GB for RZ/G2L EVK**                          |
            |           | - **150 GB for RZ/G2LC EVK**                         |
            |           | - **85 GB for RZ/G2UL EVK**                          |
            |           +-------------+----------------------------------------+
            |           | OS          | **Ubuntu 22.04 LTS**                   |
            |           |             |                                        |
            |           |             | 64bit OS must be used.                 |
            +-----------+-------------+----------------------------------------+
