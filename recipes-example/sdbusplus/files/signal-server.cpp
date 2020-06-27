#include <iostream>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/bus/match.hpp>
#include <sdbusplus/server.hpp>

static int caughtSignal(sd_bus_message* msg,
                        void* userData,
                        sd_bus_error* retError)
{
    auto sdPlusMsg = sdbusplus::message::message(msg);

    fprintf(stderr, "Message Signature: %s\n", sdPlusMsg.get_signature());

    bool result;
    sdPlusMsg.read(result);
    fprintf(stderr, "%d\n", result);
    int16_t result2;
    sdPlusMsg.read(result2);
    fprintf(stderr, "0x%hX\n", result2);
    uint16_t result3;
    sdPlusMsg.read(result3);
    fprintf(stderr, "0x%hX\n", result3);
    int32_t result4;
    sdPlusMsg.read(result4);
    fprintf(stderr, "0x%X\n", result4);
    uint32_t result5;
    sdPlusMsg.read(result5);
    fprintf(stderr, "0x%X\n", result5);
    int64_t result6;
    sdPlusMsg.read(result6);
    fprintf(stderr, "0x%llX\n", result6);
    uint64_t result7;
    sdPlusMsg.read(result7);
    fprintf(stderr, "0x%llX\n", result7);
    std::string result8;
    sdPlusMsg.read(result8);
    fprintf(stderr, "%s\n", result8.c_str());

    return 0;
}

bool cmdDone = false;

int main(int argc, char *argv[])
{
    // Define a dbus path location to place the object.
    constexpr auto path = "/xyz/openbmc_project/state/abc";

    // Create a new bus and affix an object manager for the subtree path we
    // intend to place objects at..
    auto bus = sdbusplus::bus::new_default();
    sdbusplus::server::manager_t m{bus, path};
    
    // Reserve the dbus service name
    bus.request_name("xyz.openbmc_project.state.abc");

    
    // Monitor for a specific signal 
    auto s = "type='signal',interface='xyz.openbmc_project.state.abc',member='SigInt'";

    // Setup Signal Handler
    sdbusplus::bus::match::match caughtSignals(bus,
                               s,
                               caughtSignal,
                               nullptr);

    // Wait for signal
    while(!cmdDone)
    {
        bus.process_discard();
        if (cmdDone) break;
        bus.wait();
    }


    return 0;
}
