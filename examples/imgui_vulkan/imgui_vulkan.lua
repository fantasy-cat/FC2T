--[[
    @title
        imgui_vulkan

    @author
        typedef

    @description
        example of using FC2T with ImGui and Vulkan render
--]]
local modules = require( "modules" ) -- lib_modules
local imgui_vulkan = {}

function imgui_vulkan.on_worker( )

    -- draw text
    modules.kernel:text(
        "Hello World. This is a test!",
        18,
        250,
        250
    )

    modules.kernel:line(
        20,
        20,
        450,
        20,
        3,
        color:new( 255, 0, 0, 255 )
    )

    modules.kernel:box(
        120,
        120,
        450,
        200,
        3,
        color:new( 0, 255, 0, 255 )
    )

    modules.kernel:boxf(
        120,
        350,
        450,
        100,
        color:new( 0, 0, 255, 255 )
    )

end

function imgui_vulkan.on_team_call( identifier )

    if identifier == "name" then
        return fantasy.session.username

    elseif identifier == "reload_scripts" then

        -- https://constelia.ai/sdk/FC2/modules/scripts/
        local scripts = fantasy.scripts()

        -- reset scripts
        scripts:reset(true)

    end
end

return imgui_vulkan
