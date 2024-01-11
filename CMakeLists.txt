
cmake_minimum_required(VERSION 3.27)

project(example_hello_world)
project(example_api)
project(example_call)
project(example_memory)
project(example_http)
project(example_ping_pong)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(example_hello_world examples/hello_world/main.cc)
add_executable(example_api examples/api/main.cc)
add_executable(example_call examples/call/main.cc)
add_executable(example_memory examples/memory/main.cc)
add_executable(example_http examples/http/main.cc)
add_executable(example_ping_pong examples/ping_pong/main.cc)
