#include <string_interner.hpp>

namespace ie {

InternedString StringInterner::get_or_intern(const std::string& string) {
    if (string.empty()) {
        return InternedString();
    }
    auto insert_result = m_strings.insert(string);
    return InternedString(std::string_view(*insert_result.first));
}

InternedString StringInterner::get_or_intern(std::string&& string) {
    if (string.empty()) {
        return InternedString();
    }
    auto insert_result = m_strings.insert(string);
    return InternedString(std::string_view(*insert_result.first));
}

InternedString StringInterner::get_or_intern(std::string_view string) {
    if (string.empty()) {
        return InternedString();
    }
    return get_or_intern(std::string(string.data(), string.size()));
}
}    // namespace ie
