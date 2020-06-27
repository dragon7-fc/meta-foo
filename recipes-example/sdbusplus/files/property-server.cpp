#include <xyz/openbmc_project/pqr/manager/client.hpp>
#include <xyz/openbmc_project/pqr/manager/server.hpp>
#include <sdbusplus/server.hpp>

#include <iostream>
#include <string_view>

using manager =
    sdbusplus::server::object_t<sdbusplus::xyz::openbmc_project::pqr::server::manager>;

int main()
{
    // Define a dbus path location to place the object.
    constexpr auto path = "/xyz/openbmc_project/pqr/manager";

    static_assert(
        std::string_view(
            sdbusplus::xyz::openbmc_project::pqr::client::manager::interface) ==
        std::string_view(manager::interface));

    // Create a new bus and affix an object manager for the subtree path we
    // intend to place objects at..
    auto b = sdbusplus::bus::new_default_system();
    sdbusplus::server::manager_t m{b, path};

    // Reserve the dbus service name : xyz.openbmc_project.pqr.manager
    b.request_name("xyz.openbmc_project.pqr.manager");

    // Create a d123 object at /xyz/openbmc_project/pqr/manager
    manager c1{b, path};

    // Handle dbus processing forever.
    while (1)
    {
        b.process_discard(); // discard any unhandled messages
        b.wait();
    }

    return 0;
}
