#
# Intent Extractor library
#

add_library(entities STATIC)

target_sources(entities PRIVATE
    include/location_entity.hpp
    include/date_time_entity.hpp
    src/date_time_entity.cpp
    src/location_entity.cpp
)

target_link_libraries(entities
    PUBLIC intent_extractor_lib
)

target_include_directories(entities
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#add_subdirectory(tests)
