#pragma once

#include <intent.hpp>
#include <date_time_entity.hpp>
#include <location_entity.hpp>


namespace ie {

    class WeatherIntent final : public Intent {
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

        const LocationEntity& location_entity() const {return m_location_entity;};

        const DateTimeEntity& date_time_entity() const {return m_date_time_entity;}
    private:
        LocationEntity m_location_entity;
        DateTimeEntity m_date_time_entity;
    };

    IE_DERIVE_INTENT_BUILD(WeatherIntent);
}