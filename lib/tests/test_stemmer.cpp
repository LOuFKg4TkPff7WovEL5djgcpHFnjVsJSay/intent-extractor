#include <catch.hpp>
#include <stemmer.hpp>

TEST_CASE("DefaultStemmer: Basic checks") {
    ie::DefaultStemmer stemmer;

    {
        std::string input = "having";
        const char* expected = "hav";
        stemmer.stem(input);
        CHECK(input == expected);
    }
    {
        std::string input = "sara's";
        const char* expected = "sara";
        stemmer.stem(input);
        CHECK(input == expected);
    }
    {
        std::string input = "lovely";
        const char* expected = "love";
        stemmer.stem(input);
        CHECK(input == expected);
    }
    {
        std::string input = "disturbed";
        const char* expected = "disturb";
        stemmer.stem(input);
        CHECK(input == expected);
    }
}
