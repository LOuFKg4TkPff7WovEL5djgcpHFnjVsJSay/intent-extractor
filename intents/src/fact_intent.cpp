#include <fact_intent.hpp>
#include <tokenizer.hpp>
namespace ie {

    bool FactIntent::initialize(IntentExtractor&) {
        return true;
    }

    std::string_view FactIntent::name() const {
        return "fact";
    }

    void FactIntent::scan_for_entities(std::size_t location_of_intent, std::string_view original_text,
                                          std::span<Token> tokens) {
        // This is assuming that most quest about facts will be along the line of
        // ... fact about <subject>;
        // One way to improve this would be to filter out words for substantives and ignore everything else
        if (location_of_intent + 1 < tokens.size()) {
            const auto& next_token = tokens[location_of_intent + 1];
            m_subject = std::string(original_text.substr(next_token.start, next_token.length));
        }

    }

    void FactIntent::log_result(std::ostream &stream) const {
        stream << "Get Fact";
        if (m_subject) {
            stream << " Subject:" << *m_subject;
        }
    }

}
