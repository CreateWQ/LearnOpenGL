cmake_minimum_required(VERSION 3.0.0)

project(LearnOpenGL)

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "C:/src/vcpkg/packages/glad_x64-windows/")

file(GLOB files ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(src)

find_package(glfw3 REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(LearnOpenGL ${files})


target_link_libraries(LearnOpenGL PRIVATE glfw)
target_link_libraries(LearnOpenGL PRIVATE glad::glad)