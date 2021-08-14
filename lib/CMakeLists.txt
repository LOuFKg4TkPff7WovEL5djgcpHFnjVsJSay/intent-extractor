#
# Intent Extractor library
#

add_library(intent_extractor_lib STATIC)

target_sources(intent_extractor_lib PRIVATE
    include/lib.hpp
    include/string_interner.hpp
    include/tokenizer.hpp
    include/stemmer.hpp
    include/intent.hpp
    include/intent_factory.hpp

    src/lib.cpp
    src/string_interner.cpp
    src/tokenizer.cpp
    src/stemmer.cpp
    src/intent_factory.cpp
)

target_link_libraries(intent_extractor_lib
    PUBLIC thirdparty_span
)

target_include_directories(intent_extractor_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(tests)