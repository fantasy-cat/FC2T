/**
 * @file main.cc
 * @author typedef
 * @brief mouse simulation. this can be done with fc2::call, but fc2::input is faster and better to use.
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief setup fc2k or zombiefc2 first since FC2 does not allow the input module to work with standard protection.
     *
     * this is irrelevant for Linux users.
     */
    fc2::setup();

    /**
     * @brief move cursor 1 pixel right and down, 150 times.
     *
     * this should create a smoothing mouse movement action. obviously you would simply do the following for something instant:
     * @code
     * fc2::input::move( 150, 150 );
     * @endcode
     *
     */
    for( auto i = 0; i < 150; i ++ )
    {
        fc2::input::move( 1, 1 );
    }

    /**
     * @brief right click
     *
     * this might happen before your mouse is done moving because fc2:multicore_input is enabled.
     */
    fc2::input::click( FC2_TEAM_MOUSE_RIGHT );
    return 0;
}