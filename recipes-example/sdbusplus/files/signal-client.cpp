#include <sdbusplus/bus.hpp>

#include <cstdint>
#include <iostream>

/** An example dbus client application.
 *  Signal xyz.openbmc_project.state.abc's SigInt interface.
 */

int main(int argc, char* argv[])
{
    using namespace sdbusplus;

    auto b = bus::new_default_system();

    // Reserve the dbus service name
    b.request_name("test.signal.source");

    auto m =
        b.new_signal(
                "/xyz/openbmc_project/state/abc",
                "xyz.openbmc_project.state.abc", 
                "SigInt"
                );
    
    /* setup default method parameters. */
    bool def_bool = true;
    int16_t def_int16 = (int16_t)std::stoi("0xFFFF", nullptr, 16);
    uint16_t def_uint16 = (uint16_t)std::stoi("0xFFFF", nullptr, 16);
    int32_t def_int32 = (int32_t)std::stol("0x7FFFFFFF", nullptr, 16);
    uint32_t def_uint32 = (uint32_t)std::stoul("0xFFFFFFFF", nullptr, 16);
    int64_t def_int64 = (int64_t)std::stoll("0x7FFFFFFFFFFFFFFF", nullptr, 16);
    uint64_t def_uint64 = (uint64_t)std::stoull("0xFFFFFFFFFFFFFFFF", nullptr, 16);
    std::string def_str = "test";

    /* apply command line parameters. */
    for (int i = 0; i < argc; i ++)
    {
        if (i == 1)
        {
            if (std::string(argv[i]).compare(std::string("false")) == 0)
            {
                def_bool = false;
            }
        }
        else if (i == 2)
        {
            def_int16 = (int16_t)std::stoi(argv[i], nullptr, 16);
        }
        else if (i == 3)
        {
            def_uint16 = (uint16_t)std::stoi(argv[i], nullptr, 16);
        }
        else if (i == 4)
        {
            def_int32 = (int32_t)std::stol(argv[i], nullptr, 16);
        }
        else if (i == 5)
        {
            def_uint32 = (uint32_t)std::stoul(argv[i], nullptr, 16);
        }
        else if (i == 6)
        {
            def_int64 = (int64_t)std::stoll(argv[i], nullptr, 16);
        }
        else if (i == 7)
        {
            def_uint64 = (uint64_t)std::stoull(argv[i], nullptr, 16);
        }
        else if (i == 8)
        {
            def_str = argv[i];
        }
        else if (i >= 9)
        {
            break;
        }
    }

    std::tuple <bool, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, std::string> def;
    def = std::make_tuple(def_bool, def_int16, def_uint16, def_int32, def_uint32, def_int64, def_uint64, def_str);
   
    m.append(std::get<0>(def), std::get<1>(def), std::get<2>(def), std::get<3>(def), std::get<4>(def), std::get<5>(def), std::get<6>(def), std::get<7>(def));
    m.signal_send();

    return 0;
}
