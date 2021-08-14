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
        ie::Token{interner.get_or_intern(std::string("what")), 0, 4},
        ie::Token{interner.get_or_intern(std::string("weather")), 5, 7},
        ie::Token{interner.get_or_intern(std::string("today")), 13, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);

    CHECK(input.substr(list[0].start, list[0].length) == "What");
    CHECK(input.substr(list[1].start, list[1].length) == "weather");
    CHECK(input.substr(list[2].start, list[2].length) == "Today");
}

TEST_CASE_METHOD(
    TokenizerTest,
    "Tokenizer: Basic lower case conversion, no special actions + untrimmed sentence") {
    const std::string_view input = "  What  weather Today  ";
    const ie::TokenList expected = {
        ie::Token{interner.get_or_intern(std::string("what")), 2, 4},
        ie::Token{interner.get_or_intern(std::string("weather")), 8, 7},
        ie::Token{interner.get_or_intern(std::string("today")), 16, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
    CHECK(input.substr(list[0].start, list[0].length) == "What");
    CHECK(input.substr(list[1].start, list[1].length) == "weather");
    CHECK(input.substr(list[2].start, list[2].length) == "Today");
}

TEST_CASE_METHOD(TokenizerTest,
                 "Tokenizer: Basic lower case conversion, no special actions + tabs, newline") {
    const std::string_view input = " \t What \r\n  weather Today \n ";
    const ie::TokenList expected = {
        ie::Token{interner.get_or_intern(std::string("what")), 3, 4},
        ie::Token{interner.get_or_intern(std::string("weather")), 12, 7},
        ie::Token{interner.get_or_intern(std::string("today")), 20, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
    CHECK(input.substr(list[0].start, list[0].length) == "What");
    CHECK(input.substr(list[1].start, list[1].length) == "weather");
    CHECK(input.substr(list[2].start, list[2].length) == "Today");
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: Punctuation removal") {
    const std::string_view input = "What, weather : Today?.";
    const ie::TokenList expected = {
        ie::Token{interner.get_or_intern(std::string("what")), 0, 4},
        ie::Token{interner.get_or_intern(std::string("weather")), 6, 7},
        ie::Token{interner.get_or_intern(std::string("today")), 16, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
    CHECK(input.substr(list[0].start, list[0].length) == "What");
    CHECK(input.substr(list[1].start, list[1].length) == "weather");
    CHECK(input.substr(list[2].start, list[2].length) == "Today");
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: Filler words removal") {
    const std::string_view input = "What is the weather like today?";
    const ie::TokenList expected = {
        ie::Token{interner.get_or_intern(std::string("what")), 0, 4},
        ie::Token{interner.get_or_intern(std::string("weather")), 12, 7},
        ie::Token{interner.get_or_intern(std::string("today")), 25, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}

TEST_CASE_METHOD(TokenizerTest, "Tokenizer: stemming") {
    const std::string_view input = "having Sara's disturbed lovely lunch?";
    const ie::TokenList expected = {
        ie::Token{interner.get_or_intern(std::string("hav")), 0, 6},
        ie::Token{interner.get_or_intern(std::string("sara")), 7, 6},
        ie::Token{interner.get_or_intern(std::string("disturb")), 14, 9},
        ie::Token{interner.get_or_intern(std::string("love")), 24, 6},
        ie::Token{interner.get_or_intern(std::string("lunch")), 31, 5},
    };
    const ie::TokenList list = tokenizer.tokenize(interner, input);
    CHECK(expected == list);
}
