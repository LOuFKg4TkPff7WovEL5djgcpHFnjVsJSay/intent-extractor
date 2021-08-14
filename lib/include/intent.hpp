#pragma once

#include <iostream>
#include <memory>
#include <span.hpp>

namespace ie {
class InternedString;
class Token;
class IntentExtractor;

/// Represents an intent type. Once an intent has been located, it can scan the remaining tokens for
/// entities of interest.
class Intent {
   public:
    virtual ~Intent() = default;

    virtual bool initialize(IntentExtractor& extractor) {return true;}

    virtual std::string_view name() const = 0;

    /// Search remaining tokens for entities of interest.
    /// \param location_of_intent Index of the the current intent in the token list
    virtual void scan_for_entities(std::size_t location_of_intent,
                                   std::string_view original_text,
                                   std::span<Token> tokens) = 0;

    /// Log the intent to the given stream
    virtual void log_result(std::ostream& stream) const = 0;
};

/// Derive this class to register with the IntentFactory
class IntentBuilder {
   public:
    virtual ~IntentBuilder() = default;

    /// Return list of keywords that activate this itentn
    virtual std::span<const std::string_view> keywords() const = 0;
    /// Create new instance of this intent
    virtual std::unique_ptr<Intent> create() const = 0;
};
}    // namespace ie

/// Derive the builders for the intent classes.
/// E.g.: IE_DERIVE_INTENT_BUILDER(MyIntent, "MyKeyword1", "MyKeyWord2")
#define IE_DERIVE_INTENT_BUILDER(class, ...)                                                      \
    struct class##Builder final : public ie::IntentBuilder {                                      \
        std::unique_ptr<ie::Intent> create() const override { return std::make_unique<class>(); } \
        std::span<const std::string_view> keywords() const override {                             \
            static const std::string_view KEYWORDS[] = {__VA_ARGS__};                             \
            return KEYWORDS;                                                                      \
        }                                                                                         \
    }
