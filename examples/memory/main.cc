/**
 * @file main.cc
 * @author typedef
 * @brief tests some basic memory operations
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief this uses the same protection mode you are using with FC2. meaning, if you have FC2K on, FC2 will use kernel mode protection to do the operations below.
     *
     * fc2::attach accepts a process name or process ID. providing a process name may create conflict if numerous processes contain the same name.
     * as written in the fc2::get_module documentation, sometimes the size of the module may return 0 for FC2K. simply restart the game. this is an FC2 issue, not FC2T.
     * fc2::get_module can be manipulated on Linux to get the write partition in memory.
     *
     * the pattern for dwLocalPlayer represents the CS2 player controller. im not 100% sure if this is still the same pattern. the way FC2 gets the localplayer is different. this was found online for the sake of an example. it's important to look at the fc2::pattern documentation as well. it will contain information on working with different types of executables.
     * read_memory is an std::optional for safety reasons.
     */
    if( fc2::engine::attach( "cs2.exe" ) )
    {
        auto [base, size] = fc2::engine::get_module( "client.dll" );
        if( base && size )
        {
            auto dwLocalPlayer = fc2::engine::pattern( "client.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 4F", 3 );
            if( dwLocalPlayer )
            {
                auto localplayer = fc2::engine::read_memory< unsigned long long >( base + dwLocalPlayer );
                if( localplayer )
                {
                    std::printf( "localplayer found: 0x%llX", localplayer.value_or( 0 ) );
                }
            }
        }
    }
    return 0;
}