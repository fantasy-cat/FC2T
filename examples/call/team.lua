local team = {}

function team.on_team_call( identifier, data )

    if identifier == "hello_world" then
        return 1337

    elseif identifier == "hello_world_2" then
        return "beep boop robot"

    elseif identifier == "hello_world_3" then
        return 10.11

    elseif identifier == "hello_world_4" then
        local achievements = fantasy.achievements()

        for _, achievement in pairs( achievements:list() ) do
            fantasy.log("{}", achievement.name )
        end

    elseif identifier == "hello_world_5" then
        for key, value in pairs( data ) do
            fantasy.log("{}: {}", key, value)
        end

    elseif identifier == "hello_world_6" then
        return data.secret_number * 10

    end

end

return team
