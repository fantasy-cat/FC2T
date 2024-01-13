/**
 * @file vulkan.hpp
 * @author typedef
 * @brief imgui and vulkan namespace header
 */

#ifndef EXAMPLE_IMGUI_VULKAN_HPP
#define EXAMPLE_IMGUI_VULKAN_HPP

#include <imgui.h> /** dear imgui 1.90.2 (https://aur.archlinux.org/packages/imgui) **/

namespace vulkan
{
    /**
     * @brief init vulkan and
     * @param name
     * @param win_w
     * @param win_h
     * @return
     */
    extern auto init( const char * name, int win_w, int win_h ) -> bool;

    /**
     * @brief render callback
     * @param io
     */
    extern auto on_render( ImGuiIO & io ) -> void;
}

#endif //EXAMPLE_IMGUI_VULKAN_HPP
