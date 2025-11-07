cmake_minimum_required(VERSION 3.10.0)
project(skia-template VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(skia-template main.cpp)

target_include_directories(
    skia-template
    PUBLIC
    ${CMAKE_SOURCE_DIR}/external/
    ${CMAKE_SOURCE_DIR}/external/skia
    ${CMAKE_SOURCE_DIR}/external/skia/third_party/externals/angle2/include
)

target_link_libraries(
    skia-template
    PUBLIC
    ${CMAKE_SOURCE_DIR}/external/skia/out/Static/libskia.a
)

if (${APPLE})
target_link_libraries(
    skia-template
    PUBLIC
    "-framework CoreServices"
    "-framework CoreFoundation"
    "-framework CoreGraphics"
    "-framework CoreText"
)
endif()
