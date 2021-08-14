#include <location_entity.hpp>

#include <stemmer.hpp>
#include <tokenizer.hpp>
#include <lib.hpp>

namespace ie {

    void LocationEntity::scan_tokens(const std::size_t intent_location, std::string_view text, std::span<Token> tokens) {
        m_location_results.clear();
        // Start search to the right
        for (auto it = tokens.begin() + intent_location + 1; it != tokens.end(); ++it) {
            if (m_location_set.find(it->processed) != m_location_set.end()) {
                m_location_results.push_back(std::string(text.substr(it->start, it->length)));
            }
        }

        if (m_location_results.empty()) {
            // If we didn't find any locations to the right, there may be some locations on the left
            // e.g: What is Paris' weather ?
            for (auto it = tokens.rbegin() + (tokens.size() - intent_location); it != tokens.rend(); ++it) {
                if (m_location_set.find(it->processed) != m_location_set.end()) {
                    m_location_results.push_back(std::string(text.substr(it->start, it->length)));
                }
            }
        }
    }

    void LocationEntity::initialize(IntentExtractor &extractor) {
        // Under normal circumstances you'd want to hook this up to a location service or pre-build some location
        // list ahead of time. For the sake of this test we will only limit the locations to the following list

        Stemmer* stemmer = extractor.tokenizer().stemmer();
        StringInterner& interner = extractor.string_interner();

        const std::string_view locations[] = {
                "paris",
                "london",
                "lisbon",
                "berlin",
        };

        std::string tmp;
        for (const auto& location : locations) {
            if (stemmer != nullptr) {
                tmp = location;
                stemmer->stem(tmp);
                m_location_set.insert(interner.get_or_intern(tmp));
            } else {
                m_location_set.insert(interner.get_or_intern(location));
            }
        }

    }

}