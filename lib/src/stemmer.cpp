#include <stemmer.hpp>

namespace ie {

static const std::string_view STEM_SUFFIX_TABLE[] = {
    "ing",
    "'s",
    "ed",
    "ly",
};

bool DefaultStemmer::stem(std::string& string) {
    // Perform some very basic string stemming
    auto ends_with = [](std::string_view str, std::string_view key) -> bool {
        if (str.size() < key.size()) {
            return false;
        }
        return str.substr(str.size() - key.size()) == key;
    };

    for (const auto& stem : STEM_SUFFIX_TABLE) {
        if (ends_with(string, stem)) {
            string.erase(string.begin() + (string.size() - stem.size()), string.end());
            return true;
        }
    }
    return false;
}
};    // namespace ie
