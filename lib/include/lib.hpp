#pragma once

#include <optional>

#include <intent_factory.hpp>
#include <string_interner.hpp>
#include <tokenizer.hpp>

namespace ie {
class Intent;

struct IntentExtractorResult {
    std::unique_ptr<Intent> intent;
    std::size_t start_of_keyword;
    std::size_t length_of_keyword;
};

/// Scans a given input and resolves a possible intent
class IntentExtractor {
   public:
    IntentExtractor();
    ~IntentExtractor();
    IntentExtractor(const IntentExtractor&) = delete;
    IntentExtractor& operator=(const IntentExtractor&) = delete;
    IntentExtractor(IntentExtractor&&) noexcept = default;
    IntentExtractor& operator=(IntentExtractor&&) noexcept = default;

    StringInterner& string_interner() { return m_string_interner; }

    Tokenizer& tokenizer() { return m_tokenizer; }

    IntentFactory& intent_factory() { return m_itnent_factory; }

    /// Extract the intent from the given text
    std::optional<IntentExtractorResult> extract_intent(std::string_view text);

   private:
    StringInterner m_string_interner;
    Tokenizer m_tokenizer;
    IntentFactory m_itnent_factory;
    TokenList m_tokens;
};
}    // namespace ie