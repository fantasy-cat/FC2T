/**
*  @file main.cc
 * @author typedef
 * @brief draws a box and a "hello world" text through fc2kv or if an overlay is running.
 */
#include <fc2.hpp>

int main( )
{
    /**
     * simply request rendering of a box and text until the solution is closed.
     */
    while ( true )
    {
        if ( fc2::get_error() != FC2_TEAM_ERROR_NO_ERROR ) break;

        fc2::draw::box(
            0,
            0,
            250,
            250,
            255,
            0,
            0,
            255,
            1
        );

        fc2::draw::text(
            "hello world",
            14,
            100,
            100,
            255,
            255,
            255,
            255
        );
    }
}