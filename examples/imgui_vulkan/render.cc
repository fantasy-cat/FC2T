/**
 * @file render.cc
 * @author typedef
 * @brief render callback
 */

#include "vulkan.hpp" /** vulkan header **/
#include <fc2.hpp> /** fc2t **/

auto vulkan::on_render( ImGuiIO & io ) -> void
{
    /**
     * @brief call on_team_call from imgui_vulkan.lua, which should be loaded in Universe4 first. this will get our username. we don't need to keep calling this per frame, hence why it is static.
     *
     */
    static auto name = fc2::call< std::string >( "name", FC2_LUA_TYPE_STRING );

    /**
     * @brief setup window
     */
    ImGui::SetNextWindowSize( ImVec2( 256, 256 ) );
    ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );

    if( ImGui::Begin( "FC2T Test" ) )
    {
        /**
         * @brief greetings
         */
        ImGui::Text( "Hello %s", name.c_str() );

        /**
         * @brief protection modes
         */
        if( ImGui::Button( "Standard" ) )
        {
            fc2::api( "setProtection&protection=0");
        }
        ImGui::SameLine();

        if( ImGui::Button( "Zombie/IPC" ) )
        {
            fc2::api( "setProtection&protection=1");
        }
        ImGui::SameLine();

        if( ImGui::Button( "Kernel" ) )
        {
            fc2::api( "setProtection&protection=2");
        }

        /**
         * @brief reload scripts button
         */
        if( ImGui::Button( "Reload Scripts" ) )
        {
            fc2::call("reload_scripts");
        }

        ImGui::End();
    }
}