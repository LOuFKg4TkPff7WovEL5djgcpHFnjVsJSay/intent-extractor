#
# Intent Extractor library
#

add_library(intents STATIC)

target_sources(intents PRIVATE
    include/weather_intent.hpp
    src/weather_intent.cpp
)

target_link_libraries(intents
    PUBLIC intent_extractor_lib
    PUBLIC entities
)

target_include_directories(intents
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(tests)
