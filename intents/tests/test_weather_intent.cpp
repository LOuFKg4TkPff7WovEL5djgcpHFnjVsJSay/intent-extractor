#include <catch.hpp>

#include <lib.hpp>
#include <weather_intent.hpp>
#include <iostream>

struct WeatherIntentTest {
    ie::IntentExtractor extractor;

    WeatherIntentTest() {
        const auto register_result = extractor.intent_factory().register_builder(
            extractor.string_interner(), std::make_shared<ie::WeatherIntentBuilder>());
        REQUIRE(register_result == ie::IntentFactoryRegistrationResult::Ok);
    }
};

static bool has_date_time(const ie::Intent& intent, std::string_view expected) {
    const ie::WeatherIntent& we = static_cast<const ie::WeatherIntent&>(intent);
    auto date_time_result = we.date_time_entity().date_time();
    if (date_time_result) {
        return *date_time_result == expected;
    }
    return false;
}

static bool has_locations(const ie::Intent& intent, std::span<const std::string_view> expected) {
    const ie::WeatherIntent& we = static_cast<const ie::WeatherIntent&>(intent);
    const auto locations = we.location_entity().locations();
    std::size_t expectedCount = 0;
    for (const auto& expected_location : expected) {
        for (const auto& location : locations) {
            if (expected_location == location) {
                ++expectedCount;
                break;
            }
        }
    }
    return expectedCount == expected.size();
}

TEST_CASE_METHOD(WeatherIntentTest, "WeatherIntent: What's the weather like today?") {
    const std::string_view input = "What is the weather like today?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_date_time(r, "today"));
}

TEST_CASE_METHOD(WeatherIntentTest, "WeatherIntent: What's the weather like in Paris today?") {
    const std::string_view input = "What is the weather like in Paris today?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_date_time(r, "today"));
    const std::string_view expected_locations[] = {
            "Paris"
    };
    CHECK(has_locations(r, expected_locations));
}

TEST_CASE_METHOD(WeatherIntentTest, "WeatherIntent: What's the weather like in Paris, London and Lisbon tomorrow?") {
    const std::string_view input = "What is the weather like in Paris, London and Lisbon tomorrow?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_date_time(r, "tomorrow"));
    const std::string_view expected_locations[] = {
            "Paris",
            "London",
            "Lisbon",
    };
    CHECK(has_locations(r, expected_locations));
}

TEST_CASE_METHOD(WeatherIntentTest, "WeatherIntent: On Wednesday, in Berlin, what is the temperature?") {
    const std::string_view input = "On Wednesday, in Berlin, what is the temperature?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_date_time(r, "Wednesday"));
    const std::string_view expected_locations[] = {
            "Berlin",
    };
    CHECK(has_locations(r, expected_locations));
}

TEST_CASE_METHOD(WeatherIntentTest, "WeatherIntent: in Berlin, Friday, weather what is?") {
    const std::string_view input = "in Berlin, Friday, weather what is?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_date_time(r, "Friday"));
    const std::string_view expected_locations[] = {
            "Berlin",
    };
    CHECK(has_locations(r, expected_locations));
}
