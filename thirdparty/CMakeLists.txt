#
# Collection of third party libraries
#
# Note: Ideally this would be using find_package() to resolve this in the most CMake like way possible and possibly be
# powered by some package manager of some sorts (e.g.: VCPKG). In the interest of saving time they have been added
# as submodules or placed directly into the repository.
#


#
# Catch2 unit tests v2.13.7 - Single Header taken directly from github release
#
add_library(thirdparty_catch2 INTERFACE)
target_include_directories(thirdparty_catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/catch2)
# Generate a catch 2 main library to compile most of catch2 once
set(catch2_main_src ${CMAKE_CURRENT_BINARY_DIR}/catch_main.cpp)
file(CONFIGURE OUTPUT ${catch2_main_src} CONTENT
    "#define CATCH_CONFIG_MAIN\n#include<catch.hpp>"
)
if (MSVC)
    # MSVC doesn't like it when main() is defined in another static library, so we use an object
    # library to work around this
    add_library(thirdparty_catch2_main OBJECT ${catch2_main_src})
else()
    add_library(thirdparty_catch2_main STATIC ${catch2_main_src})
endif()
target_link_libraries(thirdparty_catch2_main PRIVATE thirdparty_catch2)

#
# fmt formatting library - use header only version for this example, ideally we'd want this
# compiled as well. v8.0.1
#
add_library(thirdparty_fmt INTERFACE)
target_include_directories(thirdparty_fmt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include)
target_compile_definitions(thirdparty_fmt INTERFACE FMT_HEADER_ONLY=1)

#
# span - implementation of std::span for c++11 - c++17
#
add_library(thirdparty_span INTERFACE)
target_include_directories(thirdparty_span INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/span/include)
