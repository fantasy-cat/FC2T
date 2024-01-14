
cmake_minimum_required(VERSION 3.27)

project(example_hello_world)
project(example_api)
project(example_call)
project(example_memory)
project(example_http)
project(example_ping_pong)
project(example_imgui)
project(example_protection)
project(example_input)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(example_hello_world examples/hello_world/main.cc)
add_executable(example_api examples/api/main.cc)
add_executable(example_call examples/call/main.cc)
add_executable(example_memory examples/memory/main.cc)
add_executable(example_http examples/http/main.cc)
add_executable(example_ping_pong examples/ping_pong/main.cc)
add_executable(example_protection examples/protection/main.cc)
add_executable(example_input examples/input/main.cc)
add_executable(example_imgui examples/imgui_vulkan/vulkan.cc
        examples/imgui_vulkan/imgui/imgui_impl_glfw.cpp
        examples/imgui_vulkan/imgui/imgui_impl_vulkan.cpp
        examples/imgui_vulkan/main.cc
        examples/imgui_vulkan/vulkan.hpp
        examples/imgui_vulkan/render.cc)

target_link_libraries(example_imgui glfw vulkan imgui)