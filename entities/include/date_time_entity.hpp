#include <span.hpp>
#include <string>
#include <unordered_set>
#include <optional>

#include <entity.hpp>

namespace ie {
    class IntentExtractor;
    /// Identify dates and/or times in the tokens. Use date_time() after scanning to get the result;
    class DateTimeEntity final  : public Entity {
    public:
        void scan_tokens(const std::size_t intent_location, std::string_view text, std::span<Token> tokens) override;

        void initialize(IntentExtractor& extractor);

        std::optional<std::string_view> date_time() const;
    private:
        std::unordered_set<InternedString> m_date_time_set;
        std::string m_date_time_result;
    };
}
