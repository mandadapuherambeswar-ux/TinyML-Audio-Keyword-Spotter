cmake_minimum_required(VERSION 3.20)
project(TinyML_Audio_KWS C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(tinyml_kws ${SOURCES})
target_compile_options(tinyml_kws PRIVATE -Wall -Wextra -O2)
target_link_libraries(tinyml_kws PRIVATE m)
