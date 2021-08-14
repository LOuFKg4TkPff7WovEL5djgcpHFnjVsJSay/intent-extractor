#pragma once

#include <iostream>
#include <span.hpp>

namespace ie {
class InternedString;

/// Represents an intent type. Once an intent has been located, it can scan the remaining tokens for
/// entities of interest.
class Intent {
   public:
    virtual ~Intent() = default;

    virtual std::string_view name() const = 0;

    /// Search remaining tokens for entities of interest.
    /// \param location_of_intent Index of the the current intent in the token list
    virtual void scan_for_entities(std::size_t location_of_intent,
                                   std::span<InternedString> tokens) = 0;

    /// Log the intent to the given stream
    virtual void log_result(std::ostream& stream) const = 0;
};

/// Derive this class to register with the IntentFactory
class IntentBuilder {
   public:
    virtual ~IntentBuilder() = default;
    /// Create new instance of this intent
    virtual std::unique_ptr<Intent> create() const = 0;
};
}    // namespace ie

#define IE_DERIVE_INTENT_BUILD(class)                                                             \
    struct class##Builder final : public ie::IntentBuilder {                                      \
        std::unique_ptr<ie::Intent> create() const override { return std::make_unique<class>(); } \
    }
