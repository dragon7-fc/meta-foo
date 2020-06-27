#include <sdbusplus/bus.hpp>

#include <cstdint>
#include <iostream>

/** An example dbus client application.
 *  Calls xyz.openbmc_project.pqr.manager's LastResult interface.
 */

int main(int argc, char *argv[])
{
    using namespace sdbusplus;

    if (argc >= 2)
    {
        /* set LastResult property */
        auto b = bus::new_default_system();
        auto m = b.new_method_call(
                    "xyz.openbmc_project.pqr.manager", 
                    "/xyz/openbmc_project/pqr/manager", 
                    "org.freedesktop.DBus.Properties", 
                    "Set"
                    );
        m.append("xyz.openbmc_project.pqr.manager", "LastResult");
        std::variant<int64_t> def;
        def = std::stoi(argv[1]);
        m.append(def);
        b.call(m);
    }
    
    /* get LastResult property */
    auto b = bus::new_default_system();
    auto m = b.new_method_call(
                "xyz.openbmc_project.pqr.manager", 
                "/xyz/openbmc_project/pqr/manager", 
                "org.freedesktop.DBus.Properties", 
                "Get"
                );
    m.append("xyz.openbmc_project.pqr.manager", "LastResult");
    std::variant<int64_t> result;
    m.append(result);
    auto reply = b.call(m);
    reply.read(result);
    fprintf(stderr, "LastResult: %lld\n", std::get<int64_t>(result));

    return 0;
}
