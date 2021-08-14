#include <weather_intent.hpp>

namespace ie {

    bool WeatherIntent::initialize(IntentExtractor& extractor) {
        m_date_time_entity.initialize(extractor);
        m_location_entity.initialize(extractor);
        return true;
    }

    std::string_view WeatherIntent::name() const {
        return "weather";
    }

    void WeatherIntent::scan_for_entities(std::size_t location_of_intent, std::string_view original_text,
                                          std::span<Token> tokens) {
        m_date_time_entity.scan_tokens(location_of_intent, original_text, tokens);
        m_location_entity.scan_tokens(location_of_intent, original_text, tokens);
    }

    void WeatherIntent::log_result(std::ostream &stream) const {
        stream << "Get Weather";
        const auto date_time_result = m_date_time_entity.date_time();
        if (date_time_result) {
            stream << " TimeDate:" << *date_time_result;
        }
        const auto location_results = m_location_entity.locations();
        for (const auto& location : location_results) {
            stream <<" Location:" << location;
        }
    }

}