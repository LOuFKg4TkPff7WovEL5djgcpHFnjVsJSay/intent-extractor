#
# intent extractor test cases
#

add_executable(intent_extractor_lib_tests)

target_sources(intent_extractor_lib_tests PRIVATE
    test_string_interner.cpp
    test_tokenizer.cpp
    test_stemmer.cpp
    test_intent_extractor.cpp
)

target_link_libraries(intent_extractor_lib_tests PRIVATE
    intent_extractor_lib
    thirdparty_fmt
    thirdparty_catch2
    thirdparty_catch2_main
)

add_test(NAME IntententExtractorLib COMMAND intent_extractor_lib_tests)