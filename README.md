This README file contains information on the contents of the meta-foo layer.

Please see the corresponding sections below for details.

Table of Contents
=================

  I. Adding the meta-foo layer to your build  
 II. example-sdbusplus recipe  
III. Misc  


I. Adding the meta-foo layer to your build
=================================================

1. Run 'bitbake-layers add-layer meta-foo'
1. echo 'IMAGE_INSTALL_append = "example-sdbusplus"' >> build/conf/local.conf

II. example-sdbusplus recipe
========
Demo sdbusplus example usage. 
    
1. Method

    1. run `method-server`

        `method-server`
    1. Verify with `method-client`

        `method-client` 

        or 

        `method-client [string] [byte digits] [byte digits] [byte digits] [byte hex]` 
    1. Verify with `dbus-send`

        `dbus-send --system --type=method_call --print-reply=literal --dest=xyz.openbmc_project.abc.d123 /xyz/openbmc_project/abc/d123 xyz.openbmc_project.abc.d123.addoem string:"haha" array:byte:1,2,3 byte:0xe0`

        - output

        ```
        Hi from the addoem method
        haha
        1 2 3
        224
        ```
1. Property

    1. run `property-server`

        `property-server`
    1. verfiy with `property-client`

    ```bash
    property-client [int64_t digits]

    property-client
    ```
    1. verify with `busctl`

    `busctl get-property xyz.openbmc_project.pqr.manager /xyz/openbmc
_project/pqr/manager xyz.openbmc_project.pqr.manager LastResult`

    `busctl set-property xyz.openbmc_project.pqr.manager /xyz/openbmc_project/pqr/manager xyz.openbmc_project.pqr.manager LastResult x 1`
1. Signal

    1. run `signal-server`

        `signal-server`
    1. Verify with `signal-client`

        `signal-client`

        or

        `signal-client [true|false] [int16_t hex] [uint16_t hex] [int32_t hex] [uint32_t hex] [int64_t hex] [uint64_t hes] [string]`
    1. Verify with `dbus-send`

        `dbus-send --system --type=signal --dest=xyz.openbmc_project.state.abc /xyz/openbmc_project/state/abc xyz.openbmc_project.state.abc.SigInt boolean:true int16:0xFFFF uint16:0xFFFF int32:0xFFFFFFFF uint32:0xFFFFFFFF int64:0xFFFFFFFFFFFFFFFF uint64:0xFFFFFFFFFFFFFFFF string:"test"`

        - output

        ```
        Message Signature: bnqiuxts
        1
        0xFFFF
        0xFFFF
        0x7FFFFFFF
        0xFFFFFFFF
        0x7FFFFFFFFFFFFFFF
        0xFFFFFFFFFFFFFFFF
        test
        ```

III. Misc
========
