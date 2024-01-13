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

    /**
     * @brief in this usage, we test the "json" parameter, allowing us to send data to on_team_call, which is automatically parsed by FC2 and broken down into a table.
     *
     * the outcome should appear like such in Universe4:
            [team.lua] ice_cream: true
            [team.lua] dog: cat
            [team.lua] secret_number: 1337
            [team.lua] hello: world
     */
    fc2::call( "hello_world_5", R"({ "hello": "world", "dog": "cat", "secret_number": 1337, "ice_cream": true })" );

    /**
     * @brief this example is like the example above, except we're going to not only give a value, but we will get one back!
     *
     * we will send our secret number to on_team_call (which is 10.50), then multiply the value by 10 and display that new value.
     */
    auto new_number = fc2::call< float >( "hello_world_6", FC2_LUA_TYPE_FLOAT, R"({ "secret_number": 10.50 })" );
    std::printf( "new number: %0.2f", new_number );
    return 0;
}