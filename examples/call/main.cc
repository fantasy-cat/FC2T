/**
 * @file main.cc
 * @author typedef
 * @brief tests the fc2::call method and on_team_call
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief fc2::call will trigger the "on_team_call" callback in FC2.
     *
     * see "team.lua" in this directory and "FC2_LUA_TYPE" in fc2.hpp for all types.
     *
     * the first argument is an identifier for "on_team_call". remember that in FC2, when a callback is triggered, all scripts that have the callback will react.
     * you need to provide an identifier so your project can react to the proper request.
     */
    std::printf("%d\n", fc2::call< int >( "hello_world", FC2_LUA_TYPE_INT ) );
    std::printf("%s\n", fc2::call< std::string >( "hello_world_2", FC2_LUA_TYPE_STRING ).c_str() );
    std::printf("%f\n", fc2::call< float >( "hello_world_3", FC2_LUA_TYPE_FLOAT ) );
    std::printf("%lf\n", fc2::call< double >( "hello_world_3", FC2_LUA_TYPE_DOUBLE ) );

    /**
     * @brief you can also use fc2::call without the need of getting a return value. if you look at "team.lua", you will notice that this specific call will list all achievements you have.
     */
    fc2::call( "hello_world_4" );
    return 0;
}