#include <catch.hpp>
#include <intent.hpp>
#include <lib.hpp>

struct TestIntent final : ie::Intent {
    std::optional<std::size_t> location;

    inline static std::string_view NAME = "test_intent";

    std::string_view name() const override { return NAME; }

    void scan_for_entities(std::size_t location_of_intent, std::span<ie::InternedString>) override {
        location = location_of_intent;
    }

    void log_result(std::ostream& stream) const override { stream << "Test Intent"; }
};

IE_DERIVE_INTENT_BUILD(TestIntent);

struct IntentExtractorTest {
    ie::IntentExtractor extractor;

    IntentExtractorTest() {
        const ie::InternedString key_words[] = {
            extractor.string_interner().get_or_intern(std::string_view("test")),
            extractor.string_interner().get_or_intern(std::string_view("test2")),
        };
        const auto register_result = extractor.intent_factory().register_builder(
            std::make_shared<TestIntentBuilder>(), key_words);
        REQUIRE(register_result == ie::IntentFactoryRegistrationResult::Ok);
    }
};

TEST_CASE_METHOD(IntentExtractorTest, "IntentExtractor: basic test") {
    const auto result = extractor.extract_intent("This is a test");
    CHECK(result);
    if (result) {
        CHECK(result->intent->name() == TestIntent::NAME);
    }
}