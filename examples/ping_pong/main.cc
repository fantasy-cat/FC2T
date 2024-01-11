/**
 * @file main.cc
 * @author typedef
 * @brief pinging fc2 and waiting for response
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief get start and stop response time from FC2. this will determine the time it took to send data back and forth.
     */
    auto [ping, pong] = fc2::ping();
    std::printf( "response time: %llu microseconds", ( pong - ping ) );
    return 0;
}