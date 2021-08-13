#
# Intent extractor binary application
#

add_executable(intent_extractor)

target_sources(intent_extractor PRIVATE
    src/main.cpp
)

target_link_libraries(intent_extractor PRIVATE intent_extractor_lib)
