cmake_minimum_required (VERSION 2.6)

project(raytracer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

add_executable(raytracer ${SOURCES})

add_subdirectory(3rdparty/lua)
add_subdirectory(3rdparty/tinyobjloader)

target_link_libraries(raytracer liblua)
target_include_directories(raytracer PUBLIC
  3rdparty/lua/src
  3rdparty/stb
  3rdparty/tinyobjloader)
