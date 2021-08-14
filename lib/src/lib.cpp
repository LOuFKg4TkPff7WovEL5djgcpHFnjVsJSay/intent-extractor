#include <intent.hpp>
#include <lib.hpp>
#include <stemmer.hpp>

namespace ie {
IntentExtractor::IntentExtractor() : m_tokenizer(std::make_unique<DefaultStemmer>()) {
    m_tokens.reserve(16);
    m_tokenizer.initialize_with_default_filler_lister(m_string_interner);
}

IntentExtractor::~IntentExtractor() {}

std::optional<IntentExtractorResult> IntentExtractor::extract_intent(std::string_view text) {
    m_tokens.clear();
    m_tokenizer.tokenize_into(m_string_interner, text, m_tokens);
    if (m_tokens.empty()) {
        return {};
    }

    /// try to locate the first valid intent based on all the words available
    for (auto it = m_tokens.begin(); it != m_tokens.end(); ++it) {
        const auto& token = *it;
        auto intent = m_itnent_factory.create_intent(token.processed);
        if (intent) {
            std::size_t distance = static_cast<size_t>(std::distance(m_tokens.begin(), it));
            intent->scan_for_entities(distance, text, m_tokens);
            return IntentExtractorResult{std::move(intent), token.start, token.length};
        }
    }
    // Failed to locate any intent
    return {};
}
}    // namespace ie