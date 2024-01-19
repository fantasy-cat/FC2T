/**
 * @file main.cc
 * @author typedef
 * @brief starts vulkan renderer and imgui
 */
#include "vulkan.hpp" /** vulkan header **/

int main( )
{
    /**
     * @brief start vulkan renderer. see render.cc
     */
    return vulkan::init( "FC2T Test", 1024, 720 );
}