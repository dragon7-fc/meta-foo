#include <sdbusplus/bus.hpp>

#include <cstdint>
#include <iostream>

/** An example dbus client application.
 *  Calls xyz.openbmc_project.abc.d123's addoem interface.
 */

int main(int argc, char* argv[])
{
    using namespace sdbusplus;

    auto b = bus::new_default_system();
    auto m =
        b.new_method_call("xyz.openbmc_project.abc.d123", 
                "/xyz/openbmc_project/abc/d123",
                "xyz.openbmc_project.abc.d123", 
                "addoem");
    
    /* setup default method parameters. */
    std::string def_str = "haha";
    std::vector<uint8_t> def_arr = {1,2,3};
    uint8_t def_byte = (uint8_t)std::stoi("0xe0", nullptr, 16);

    /* apply command line parameters. */
    for (int i = 0; i < argc; i ++)
    {
        if (i == 1)
        {
            def_str = argv[i];
        }
        else if (i == 2)
        {
            def_arr[0] = (uint8_t)std::stoi(argv[i]);
        }
        else if (i == 3)
        {
            def_arr[1] = (uint8_t)std::stoi(argv[i]);
        }
        else if (i == 4)
        {
            def_arr[2] = (uint8_t)std::stoi(argv[i]);
        }
        else if (i == 5)
        {
            def_byte = (uint8_t)std::stoi(argv[i], nullptr, 16);
        }
        else if (i > 5)
        {
            break;
        }
    }

    std::tuple <std::string, std::vector<uint8_t>, uint8_t> def;
    def = std::make_tuple(def_str, def_arr, def_byte);
   
    m.append(std::get<0>(def), std::get<1>(def), std::get<2>(def));
    b.call(m);

    return 0;
}
