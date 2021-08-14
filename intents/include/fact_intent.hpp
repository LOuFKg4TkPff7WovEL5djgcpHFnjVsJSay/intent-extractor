#pragma once

#include <optional>
#include <string>
#include <intent.hpp>

namespace ie {

    /// Fact intent gets trigger by the fact keyword and tried to locate a possible subject about which we may
    /// which to have facts about. The subject location is very simple and only works if there is a token after
    /// the location the keyword was found.
    class FactIntent final : public Intent {
    public:
        bool initialize(IntentExtractor& extractor) override;

        std::string_view name() const override;

        /// Search remaining tokens for entities of interest.
        /// \param location_of_intent Index of the the current intent in the token list
        void scan_for_entities(std::size_t location_of_intent,
                               std::string_view original_text,
                               std::span<Token> tokens) override;

        /// Log the intent to the given stream
        void log_result(std::ostream& stream) const override;

        const std::optional<std::string>& subject() const {return m_subject;};
    private:
        std::optional<std::string> m_subject;
    };

    IE_DERIVE_INTENT_BUILDER(FactIntent, "fact");
}
