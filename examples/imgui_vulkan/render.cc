/**
 * @file render.cc
 * @author typedef
 * @brief render callback
 */

#include "vulkan.hpp" /** vulkan header **/

#include <fc2.hpp> /** fc2t **/

auto vulkan::on_render( const ImGuiIO & io ) -> void
{
    /**
     * @brief call on_team_call from imgui_vulkan.lua, which should be loaded in Universe4 first. this will get our username. we don't need to keep calling this per frame, hence why it is static.
     *
     */
    static auto name = fc2::call< std::string >( "name", FC2_LUA_TYPE_STRING );

    /**
     * @brief check if the last transaction worked.
     */
    if( fc2::get_error() != FC2_TEAM_ERROR_NO_ERROR)
    {
        puts("FC2 is not running or is unresponsive.");
        std::exit( 1 );
    }

    /**
     * @brief setup window
     */
    ImGui::SetNextWindowSize( ImVec2( 256, 256 ) );
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

    ImGui::SetNextWindowSize( ImVec2( 516, 516 ) );
    if( ImGui::Begin( "FC2T Drawing Test (Fake Overlay)" ) )
    {
        /**
         * @brief let's see the frame rate of the renderer
         */
        ImGui::Text( "Frame Rate: %f", io.Framerate);

        /**
         * @brief get drawing requests that we are going to use as the content to render
         */
        auto drawing = fc2::draw::get();

        /**
         * @brief did a FC2 solution close while we had this open? nothing to draw anymore.
         */
        if( fc2::get_error() != FC2_TEAM_ERROR_NO_ERROR)
        {
            puts("FC2 is not running anymore.");
            std::exit( 1 );
        }

        /**
         * @brief loop through the drawing requests and draw based on the information we have
         */
        for( auto & [text, dimensions, style] : drawing )
        {
            /**
             * @brief get drawing canvas. this will allow us to draw in the background
             */
            const auto canvas = ImGui::GetBackgroundDrawList();

            /**
             * @brief draw text. this would be better with ImGui::TextColored, but the current version of FC2KV does not support color text. once I add that, the example will be changed.
             */
            if( style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_TEXT )
            {
                ImGui::Text( "%s", text );
            }

            /**
             * @brief draw line. nothing fancy going on here.
             */
            else if( style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_LINE )
            {
                canvas->AddLine(
                    ImVec2( dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_LEFT ], dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_TOP ]),
                    ImVec2( dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_RIGHT ], dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_BOTTOM ]),
                    ImColor( (int)style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_RED], style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_GREEN], style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_BLUE], style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_ALPHA] ),
                    style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_THICKNESS ]
                );
            }

            /**
             * @brief draw boxes. worth noting that in imgui, imvec2 wants floating values, yet the dimensions are long. these should be casted.
             */
            else if( style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_BOX || style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_BOX_FILLED )
            {
                const auto min = ImVec2( dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_LEFT ], dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_TOP ]);
                const auto max = ImVec2( min.x + dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_RIGHT ], min.y + dimensions[ FC2_TEAM_DRAW_DIMENSIONS::FC2_TEAM_DRAW_DIMENSIONS_BOTTOM ]);
                const auto clr = ImColor( static_cast< int >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_RED] ), static_cast< int >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_GREEN] ), static_cast< int >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_BLUE] ), static_cast< int >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_ALPHA] ) );

                if( style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_BOX )
                {
                    canvas->AddRect( min, max, clr, static_cast< float >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_THICKNESS ] ) );
                }
                else if( style[ FC2_TEAM_DRAW_STYLE_TYPE ] == FC2_TEAM_DRAW_TYPE_BOX_FILLED )
                {
                    canvas->AddRectFilled( min, max, clr, static_cast< float >( style[ FC2_TEAM_DRAW_STYLE::FC2_TEAM_DRAW_STYLE_THICKNESS ] ) );
                }
            }

        }
        ImGui::End();
    }
}