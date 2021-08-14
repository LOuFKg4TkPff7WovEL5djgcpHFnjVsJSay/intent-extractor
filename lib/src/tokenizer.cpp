#include <tokenizer.hpp>

#include <algorithm>
#include <cassert>

#include <stemmer.hpp>
#include <string_interner.hpp>

namespace ie {

Tokenizer::Tokenizer() {}

Tokenizer::Tokenizer(std::unique_ptr<Stemmer>&& stemmer)
    : m_stemmer(std::forward<std::unique_ptr<Stemmer>>(stemmer)) {
    assert(m_stemmer.get() != nullptr);
}

Tokenizer::~Tokenizer() {}

void Tokenizer::set_stemmer(std::unique_ptr<Stemmer>&& stemmer) {
    if (stemmer) {
        m_stemmer = std::move(stemmer);
    }
}

void Tokenizer::initialize_with_default_filler_lister(StringInterner& interner) {
    const char* filler_words[] = {
        "the", "a", "in", "about", "as", "form", "to", "like", "is",
    };

    m_filler_words.clear();
    m_filler_words.reserve(sizeof(filler_words) / sizeof(filler_words[0]));
    for (const auto& word : filler_words) {
        m_filler_words.insert(std::string(word));
    }
}

void Tokenizer::initialize_with_filler_list(StringInterner&,
                                            std::span<std::string_view> filler_words) {
    m_filler_words.clear();
    m_filler_words.reserve(filler_words.size());
    for (const auto& word : filler_words) {
        m_filler_words.insert(std::string(word));
    }
}

static inline void lower_case_string(std::string& out, std::string_view input) {
    out.reserve(input.size());
    std::transform(input.begin(), input.end(), std::back_inserter(out),
                   [](const char c) -> char { return static_cast<char>(std::tolower(c)); });
}

TokenList Tokenizer::tokenize(StringInterner& interner, std::string_view input) {
    TokenList result;
    tokenize_into(interner, input, result);
    return result;
}

void Tokenizer::tokenize_into(StringInterner &interner, std::string_view input, TokenList &outTokens) {
    if (input.empty()) {
        outTokens.clear();
    }

    outTokens.reserve(8);
    std::string tmp_string;

    auto it = input.begin();
    auto it_end = input.end();
    auto peek = [](auto it, auto it_end) -> std::optional<char> {
        if (it != it_end) {
            ++it;
            if (it != it_end) {
                return *it;
            }
        }
        return {};
    };

    while (it != input.end()) {
        const char ch = *it;

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            if (!tmp_string.empty()) {
                const auto opt_token = convert_to_token(interner, tmp_string);
                if (opt_token) {
                    outTokens.push_back(*opt_token);
                }
                tmp_string.clear();
            }
            ++it;
            continue;
        }

        // handle 's case
        if (ch == '\'') {
            const auto peeked_char = peek(it, it_end);
            if (peeked_char && std::isalpha(*peeked_char)) {
                tmp_string.push_back('\'');
                tmp_string.push_back(static_cast<char>(std::tolower(*peeked_char)));
                it += 2;
                continue;
            }
        }

        if (std::ispunct(ch)) {
            ++it;
            continue;
        }

        if (std::isalpha(ch)) {
            tmp_string.push_back(static_cast<char>(std::tolower(ch)));
        } else if (std::isdigit(ch)) {
            tmp_string.push_back(ch);
        }

        ++it;
    }
    if (!tmp_string.empty()) {
        const auto opt_token = convert_to_token(interner, tmp_string);
        if (opt_token) {
            outTokens.push_back(*opt_token);
        }
    }
}

bool Tokenizer::is_filler_world(const std::string& word) const {
    return m_filler_words.find(word) != m_filler_words.end();
}

std::optional<InternedString> Tokenizer::convert_to_token(StringInterner& interner,
                                                          std::string& string) {
    // Check if we should ignore this word
    if (is_filler_world(string)) {
        return {};
    }
    // Perform some stemming
    if (m_stemmer) {
        m_stemmer->stem(string);
    }
    // Intern result;
    return interner.get_or_intern(string);
}


}    // namespace ie