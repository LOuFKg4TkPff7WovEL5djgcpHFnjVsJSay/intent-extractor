#
# intent extractor test cases
#

add_executable(intent_tests)

target_sources(intent_tests PRIVATE
    test_weather_intent.cpp
    test_fact_intent.cpp
)

target_link_libraries(intent_tests PRIVATE
    intents
    thirdparty_fmt
    thirdparty_catch2
    thirdparty_catch2_main
)

add_test(NAME IntentTest COMMAND intent_test)