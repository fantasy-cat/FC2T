--[[
    @title
        imgui_vulkan

    @author
        typedef

    @description
        example of using FC2T with ImGui and Vulkan render
--]]
local imgui_vulkan = {}

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
