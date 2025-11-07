cmake_minimum_required(VERSION 3.10.0)
project(skia-template VERSION 0.1.0 LANGUAGES C CXX)

add_executable(skia-template main.cpp)
target_include_directories(
    skia-template
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/
    ${CMAKE_CURRENT_SOURCE_DIR}/external/skia
    ${CMAKE_CURRENT_SOURCE_DIR}/external/skia/third_party/externals/angle2/include
)
