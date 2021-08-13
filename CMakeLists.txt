cmake_minimum_required(VERSION 3.20)
project(IntentExtractor CXX)


# Set C++ standard to 17 (VS 2019 recommended)
# Note this project was tested on Linux with GCC 11.1
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable testing integration/ctest
enable_testing()

add_library(compiler_flags INTERFACE)
if (NOT MSVC)
    # NOTE: I would love to enable Werror or add the equivalent warnings for MSVC on windows, but in the interest of time
    # and because I have no idea on what platform this project will be run, I'll only activate these warnings for GCC/clang
    target_compile_options(compiler_flags INTERFACE -Wall -Wextra)
endif()

# Third party dependencies
add_subdirectory(thirdparty)

# Main library with all the logic
add_subdirectory(lib)

# Command line utility
add_subdirectory(bin)
