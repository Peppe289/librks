cmake_minimum_required(VERSION 3.27.0)
project(rks VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# C sources
file(GLOB C_SOURCES "src/*.c")

# C++ sources
file(GLOB CPP_SOURCES "src/*.cpp")

# Compile C sources
add_library(rksC OBJECT ${C_SOURCES})

# Compile C++ sources
add_library(rksCPP OBJECT ${CPP_SOURCES})

# Create shared library from C and C++ object files
add_library(rks SHARED $<TARGET_OBJECTS:rksC> $<TARGET_OBJECTS:rksCPP>)

# Set the include directories for C and C++ code
target_include_directories(rksC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(rksCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(rksC PRIVATE -Wall -Wextra -fPIC)
target_compile_options(rksCPP PRIVATE -Wall -Wextra -fPIC)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
