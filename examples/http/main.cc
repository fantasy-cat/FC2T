/**
 * @file main.cc
 * @author typedef
 * @brief tests http methods
 */
#include <fc2.hpp>
#include <format> /** std::format (req c++20) **/

int main()
{
    /**
     * @brief escapes and encodes our message for HTTP requests.
     */
    auto my_text = fc2::http::escape("Hello. What is your name?");

    /**
     * @brief send a HTTP GET request to httpbin.org/get.
     *
     * https://httpbin.org/#/HTTP_Methods/get_get
     */
    const auto get_response = fc2::http::get( std::format( "https://httpbin.org/get?message={}", my_text ) );

    /**
     * @brief do the same as above, except with post data.
     *
     * https://httpbin.org/#/HTTP_Methods/post_post
     */
    const auto post_response = fc2::http::post( "https://httpbin.org/post", std::format("message={}", my_text ) );

    std::puts( get_response.c_str() );
    std::puts( post_response.c_str() );
    return 0;
}