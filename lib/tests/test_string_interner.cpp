#include <catch.hpp>

#include <string_interner.hpp>

TEST_CASE("String Interner: Check repeated") {
    ie::StringInterner intener;
    const ie::InternedString str1 = intener.get_or_intern(std::string_view("Hello World"));
    const ie::InternedString str2 = intener.get_or_intern(std::string_view("Hello World"));
    const ie::InternedString str3 = intener.get_or_intern(std::string_view("Hello World2"));
    CHECK(str1 == str2);
    CHECK(str1 != str3);
}