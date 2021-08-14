#include <date_time_entity.hpp>
#include <lib.hpp>
#include <stemmer.hpp>
namespace ie {

    void DateTimeEntity::scan_tokens(const std::size_t intent_location, std::string_view text, std::span<Token> tokens) {
        m_date_time_result.clear();
        // Start search to the right
        for (auto it = tokens.begin() + intent_location + 1; it != tokens.end(); ++it) {
            if (m_date_time_set.find(it->processed) != m_date_time_set.end()) {
                m_date_time_result.assign(text.substr(it->start, it->length));
                break;
            }
        }

        if (m_date_time_result.empty()) {
            // If we didn't find any locations to the right, there may be some locations on the left
            // e.g: What is Paris' weather ?
            for (auto it = tokens.rbegin() + (tokens.size() - intent_location); it != tokens.rend(); ++it) {
                if (m_date_time_set.find(it->processed) != m_date_time_set.end()) {
                    m_date_time_result.assign(text.substr(it->start, it->length));
                    break;
                }
            }
        }
    }

    void DateTimeEntity::initialize(IntentExtractor& extractor) {
        // This example should be extended with a more complex parser to read and process date and time.
        // for the context of this example we will only support some keywords
        Stemmer* stemmer = extractor.tokenizer().stemmer();
        StringInterner& interner = extractor.string_interner();

        const std::string_view locations[] = {
                "today",
                "tomorrow",
                "monday",
                "tuesday",
                "wednesday",
                "thursday",
                "friday",
                "saturday",
                "sunday"
        };

        std::string tmp;
        for (const auto& location : locations) {
            if (stemmer != nullptr) {
                tmp = location;
                stemmer->stem(tmp);
                m_date_time_set.insert(interner.get_or_intern(tmp));
            } else {
                m_date_time_set.insert(interner.get_or_intern(location));
            }
        }
    }

    std::optional<std::string_view> DateTimeEntity::date_time() const {
        return !m_date_time_result.empty() ? std::optional<std::string_view>(m_date_time_result) : std::optional<std::string_view>();
    }
}