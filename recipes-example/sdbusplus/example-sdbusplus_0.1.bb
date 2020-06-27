SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"

inherit meson
inherit python3native

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=19407077e42b1ba3d653da313f1f5b4e"

DEPENDS += " \
        ${PYTHON_PN}-inflection-native \
        ${PYTHON_PN}-mako-native \
        ${PYTHON_PN}-pyyaml-native \
        boost \
        googletest \
        systemd \
        sdbusplus \
        "

SRC_URI = "file://*"
S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 method-client ${D}${bindir}
    install -m 0755 method-server ${D}${bindir}
    install -m 0755 property-client ${D}${bindir}
    install -m 0755 property-server ${D}${bindir}
    install -m 0755 signal-client ${D}${bindir}
    install -m 0755 signal-server ${D}${bindir}
}
