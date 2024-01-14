/**
 * @file main.cc
 * @author typedef
 * @brief doesn't really need an example. but this shows how basic usage of setup.
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief depending on the member's protection settings, this will install FC2K or ZombieFC2. although this function returns a boolean, usually when this method fails, the FC2 solution will close itself anyway. this will always return true otherwise.
     *
     * if the user is in standard protection mode, Universe4 will print "[team] protection mode is standard (usermode), the setup function has nothing to do". this isn't an error, but it does imply that certain restrictions may come into play (like how usermode protection cannot use the input module). for Linux users, this will always succeed.
     */
    fc2::setup();
    return 0;
}