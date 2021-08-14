#include <catch.hpp>

#include <lib.hpp>
#include <fact_intent.hpp>
#include <iostream>

struct FactIntentTest {
    ie::IntentExtractor extractor;

    FactIntentTest() {
        const auto register_result = extractor.intent_factory().register_builder(
                extractor.string_interner(), std::make_shared<ie::FactIntentBuilder>());
        REQUIRE(register_result == ie::IntentFactoryRegistrationResult::Ok);
    }
};

static bool has_subject(const ie::Intent& intent, std::string_view expected) {
    const ie::FactIntent& f = static_cast<const ie::FactIntent&>(intent);
    const auto& subject = f.subject();
    if (subject) {
        return *subject == expected;
    }
    return false;
}

static bool has_no_subject(const ie::Intent& intent) {
    const ie::FactIntent& f = static_cast<const ie::FactIntent&>(intent);
    const auto& subject = f.subject();
    return !subject.has_value();
}

TEST_CASE_METHOD(FactIntentTest, "FactIntent: Tell me an interesting fact") {
    const std::string_view input = "Tell me an interesting fact?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_no_subject(r));
}

TEST_CASE_METHOD(FactIntentTest, "FactIntent: Tell me an interesting fact about toys") {
    const std::string_view input = "Tell me an interesting fact about toys?";
    const auto result = extractor.extract_intent(input);
    REQUIRE(result.result == ie::IntentExtractorResult::Ok);
    const auto& r = *result.intent;
    r.log_result(std::cout);
    std::cout <<'\n';
    CHECK(has_subject(r, "toys"));
}