/**
 * @file main.cc
 * @author typedef
 * @brief calls setProtection on Web API
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief calls the Web API method "setProtection". this will change your protection mode to FC2K (which is default already).
     * the API result is printed after.
     *
     * https://constelia.ai/sdk/Web%20API/methods/#setprotection
     */
    auto output = fc2::api( "setProtection&protection=2");
    std::puts( output.c_str() );
    return 0;
}