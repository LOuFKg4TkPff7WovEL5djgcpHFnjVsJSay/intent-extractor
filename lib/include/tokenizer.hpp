#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include <span.hpp>

namespace ie {
class InternedString;
class StringInterner;
class Stemmer;
using TokenList = std::vector<InternedString>;

/// Converts a string to list of tokens more suitable for analysis. The tokenizer may perform the
/// following operations:
///  - lower casing
///  - remove punctuation
///  - remove filler words
///  - stemming
class Tokenizer {
   public:
    Tokenizer();

    Tokenizer(std::unique_ptr<Stemmer>&& stemmer);

    ~Tokenizer();

    void set_stemmer(std::unique_ptr<Stemmer>&& stemmer);

    void initialize_with_default_filler_lister(StringInterner& interner);

    void initialize_with_filler_list(StringInterner&, std::span<std::string_view> filler_words);

    /// Generate a list of tokens from a sentence.
    TokenList tokenize(StringInterner& interner, std::string_view input);

    /// Generate a list of tokens from a sentence.
    void tokenize_into(StringInterner& interner, std::string_view input, TokenList& outTokens);

   private:
    bool is_filler_world(const std::string& word) const;

    std::optional<InternedString> convert_to_token(StringInterner& interner, std::string& string);

   private:
    std::unique_ptr<Stemmer> m_stemmer;
    std::unordered_set<std::string> m_filler_words;
};
}    // namespace ie