#pragma once

#include <vector>
#include <span.hpp>
#include <string>
#include <entity.hpp>
#include <unordered_set>

namespace ie {
    class IntentExtractor;
    /// Scans tokens for valid location entities. Use locations() after scanning to get the results.
    class LocationEntity final  : public Entity {
    public:
        void scan_tokens(const std::size_t intent_location, std::string_view text, std::span<Token> tokens) override;

        void initialize(IntentExtractor& extractor);

        std::span<const std::string> locations() const {return m_location_results;}
    private:
        std::unordered_set<InternedString> m_location_set;
        std::vector<std::string> m_location_results;
    };
}