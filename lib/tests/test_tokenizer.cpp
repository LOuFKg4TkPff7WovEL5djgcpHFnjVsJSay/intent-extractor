#include <catch.hpp>

#include <span.hpp>

#include <stemmer.hpp>
#include <string_interner.hpp>
#include <tokenizer.hpp>

struct TokenizerTest {
    ie::StringInterner interner;
    ie::Tokenizer tokenizer;

    TokenizerTest() : tokenizer(std::make_unique<ie::DefaultStemmer>()) {
        tokenizer.initialize_with_default_filler_lister(interner);
    }
};

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: Basic lower case conversion, no special actions ") {
    const std::string_view input = "What weather Today";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("what")),
        interner.get_or_intern(std::string("weather")),
        interner.get_or_intern(std::string("today")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(
    TokenizerTest,
    "Tokenizer: Basic lower case conversion, no special actions + untrimmed sentence") {
    const std::string_view input = "  What  weather Today  ";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("what")),
        interner.get_or_intern(std::string("weather")),
        interner.get_or_intern(std::string("today")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(TokenizerTest,
                 "Tokenizer: Basic lower case conversion, no special actions + tabs, newline") {
    const std::string_view input = " \t What \r\n  weather Today \n ";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("what")),
        interner.get_or_intern(std::string("weather")),
        interner.get_or_intern(std::string("today")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: Punctuation removal") {
    const std::string_view input = "What, weather : Today?.";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("what")),
        interner.get_or_intern(std::string("weather")),
        interner.get_or_intern(std::string("today")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: Filler words removal") {
    const std::string_view input = "What is the weather like today?";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("what")),
        interner.get_or_intern(std::string("weather")),
        interner.get_or_intern(std::string("today")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: stemming") {
    const std::string_view input = "having Sara's disturbed lovely lunch?";
    const ie::TokenList expected = {
        interner.get_or_intern(std::string("hav")),     interner.get_or_intern(std::string("sara")),
        interner.get_or_intern(std::string("disturb")), interner.get_or_intern(std::string("love")),
        interner.get_or_intern(std::string("lunch")),
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}
