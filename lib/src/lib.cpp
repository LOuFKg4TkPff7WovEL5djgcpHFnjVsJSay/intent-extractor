#include <intent.hpp>
#include <lib.hpp>
#include <stemmer.hpp>

namespace ie {
IntentExtractor::IntentExtractor() : m_tokenizer(std::make_unique<DefaultStemmer>()) {
    m_tokens.reserve(16);
    m_tokenizer.initialize_with_default_filler_lister(m_string_interner);
}

IntentExtractor::~IntentExtractor() {}

IntentExtractorResultValue IntentExtractor::extract_intent(std::string_view text) {
    IntentExtractorResultValue result {};
    result.result = IntentExtractorResult::Ok;
    m_tokens.clear();
    m_tokenizer.tokenize_into(m_string_interner, text, m_tokens);
    if (m_tokens.empty()) {
        result.result = IntentExtractorResult::CouldNotFindIntent;
        return result;
    }

    /// try to locate the first valid intent based on all the words available
    for (auto it = m_tokens.begin(); it != m_tokens.end(); ++it) {
        const auto& token = *it;
        auto intent = m_itnent_factory.create_intent(token.processed);
        if (!intent) {
            continue;
        }
        if (!intent->initialize(*this)) {
            result.result = IntentExtractorResult::IntentFailedToInit;
            return result;
        }
        if (intent) {
            std::size_t distance = static_cast<size_t>(std::distance(m_tokens.begin(), it));
            intent->scan_for_entities(distance, text, m_tokens);
            result.intent = std::move(intent);
            result.start_of_keyword = token.start;
            result.length_of_keyword = token.length;
            return result;
        }
    }
    // Failed to locate any intent
    result.result = IntentExtractorResult::CouldNotFindIntent;
    return result;
}
}    // namespace ie