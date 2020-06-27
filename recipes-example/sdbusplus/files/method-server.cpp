#include <xyz/openbmc_project/abc/d123/client.hpp>
#include <xyz/openbmc_project/abc/d123/server.hpp>
#include <sdbusplus/server.hpp>

#include <iostream>
#include <string_view>

using d123_inherit =
    sdbusplus::server::object_t<sdbusplus::xyz::openbmc_project::abc::server::d123>;

/** Example implementation of xyz.openbmc_project.abc.d123 */
struct d123 : d123_inherit
{
    /** Constructor */
    d123(sdbusplus::bus::bus& bus, const char* path) :
        d123_inherit(bus, path)
    {}

    void addoem(
            std::string testString,
            std::vector<uint8_t> testArray,
            uint8_t testByte)
    {
       fprintf(stderr,"Hi from the addoem method\n");
       fprintf(stderr, "%s\n", testString.c_str());
       for (int i = 0; i < (int)testArray.size(); i++)
       {
           fprintf(stderr, "%d ", testArray[i]);
       }
       fprintf(stderr, "\n");
       fprintf(stderr, "%d\n", testByte);
    }
};

int main()
{
    // Define a dbus path location to place the object.
    constexpr auto path = "/xyz/openbmc_project/abc/d123";

    static_assert(
        std::string_view(
            sdbusplus::xyz::openbmc_project::abc::client::d123::interface) ==
        std::string_view(d123::interface));

    // Create a new bus and affix an object manager for the subtree path we
    // intend to place objects at..
    auto b = sdbusplus::bus::new_default_system();
    sdbusplus::server::manager_t m{b, path};

    // Reserve the dbus service name : xyz.openbmc_project.abc.d123
    b.request_name("xyz.openbmc_project.abc.d123");

    // Create a d123 object at /xyz/openbmc_project/abc/d123
    d123 c1{b, path};

    // Handle dbus processing forever.
    while (1)
    {
        b.process_discard(); // discard any unhandled messages
        b.wait();
    }

    return 0;
}
