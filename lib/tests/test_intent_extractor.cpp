#include <catch.hpp>
#include <intent.hpp>
#include <lib.hpp>

struct TestIntent final : ie::Intent {
    inline static std::string_view NAME = "test_intent";

    std::string_view name() const override { return NAME; }

    void scan_for_entities(std::size_t,
                           std::string_view,
                           std::span<ie::Token>) override {
    }

    void log_result(std::ostream& stream) const override { stream << "Test Intent"; }
};

struct TestIntent2 final : ie::Intent {
    inline static std::string_view NAME = "test_intent2";

    std::string_view name() const override { return NAME; }

    void scan_for_entities(std::size_t,
                           std::string_view,
                           std::span<ie::Token>) override {
    }

    void log_result(std::ostream& stream) const override { stream << "Test Intent2"; }
};

IE_DERIVE_INTENT_BUILDER(TestIntent, "test", "testalt");
IE_DERIVE_INTENT_BUILDER(TestIntent2, "test2");

struct IntentExtractorTest {
    ie::IntentExtractor extractor;

    IntentExtractorTest() {
        {
            const auto register_result = extractor.intent_factory().register_builder(
                extractor.string_interner(), std::make_shared<TestIntentBuilder>());
            REQUIRE(register_result == ie::IntentFactoryRegistrationResult::Ok);
        }
        {
            const auto register_result = extractor.intent_factory().register_builder(
                extractor.string_interner(), std::make_shared<TestIntent2Builder>());
            REQUIRE(register_result == ie::IntentFactoryRegistrationResult::Ok);
        }
    }
};

TEST_CASE_METHOD(IntentExtractorTest, "IntentExtractor: basic test") {
    const std::string_view input = "This is a Test!";
    const auto result = extractor.extract_intent(input);
    CHECK(result.result == ie::IntentExtractorResult::Ok);
    if (result.result == ie::IntentExtractorResult::Ok) {
        CHECK(result.intent->name() == TestIntent::NAME);
        CHECK(result.start_of_keyword == 10);
        CHECK(result.length_of_keyword == 4);
        CHECK(input.substr(result.start_of_keyword, result.length_of_keyword) == "Test");
    }
}

TEST_CASE_METHOD(IntentExtractorTest, "IntentExtractor: basic test alt ") {
    const std::string_view input = "This is a testalt!";
    const auto result = extractor.extract_intent(input);
    CHECK(result.result == ie::IntentExtractorResult::Ok);
    if (result.result == ie::IntentExtractorResult::Ok) {
        CHECK(result.intent->name() == TestIntent::NAME);
        CHECK(result.start_of_keyword == 10);
        CHECK(result.length_of_keyword == 7);
        CHECK(input.substr(result.start_of_keyword, result.length_of_keyword) == "testalt");
    }
}

TEST_CASE_METHOD(IntentExtractorTest, "IntentExtractor: more than one intent") {
    // Check that the returned result is the first matching intent
    const std::string_view input = "This ,test2, is a Test!";
    const auto result = extractor.extract_intent(input);
    CHECK(result.result == ie::IntentExtractorResult::Ok);
    if (result.result == ie::IntentExtractorResult::Ok) {
        CHECK(result.intent->name() == TestIntent2::NAME);
        CHECK(input.substr(result.start_of_keyword, result.length_of_keyword) == "test2");
    }
}
