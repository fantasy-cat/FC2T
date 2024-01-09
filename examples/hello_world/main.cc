/**
 * @file main.cc
 * @author typedef
 * @brief runs a "Hello World" in the FC2 solution's console.
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief call fantasy.log and print "Hello World"
     *
     * https://constelia.ai/sdk/FC2/modules/fantasy/#log
     */
    fc2::lua( "fantasy.log(\"Hello World\")" );
    return 0;
}