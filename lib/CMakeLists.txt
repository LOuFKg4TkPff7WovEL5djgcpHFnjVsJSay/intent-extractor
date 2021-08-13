#
# Intent Extractor library
#

add_library(intent_extractor_lib STATIC)

target_sources(intent_extractor_lib PRIVATE
    include/lib.hpp
    src/lib.cpp
)

target_link_libraries(intent_extractor_lib PRIVATE
    thirdparty_fmt
    thirdparty_span
)

target_include_directories(intent_extractor_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(tests)