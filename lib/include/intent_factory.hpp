#include <memory>
#include <unordered_map>

#include <span.hpp>

#include <string_interner.hpp>

namespace ie {
class Intent;
class IntentBuilder;

enum class IntentFactoryRegistrationResult {
    Ok,
    DuplicateKeyWord,
};

using IntentBuilderPtr = std::shared_ptr<IntentBuilder>;

/// Registration point for intents to be used during recognition
class IntentFactory final {
   public:
    IntentFactory();
    ~IntentFactory();
    IntentFactory(const IntentFactory&) = delete;
    IntentFactory& operator=(const IntentFactory&) = delete;
    IntentFactory(IntentFactory&&) noexcept = default;
    IntentFactory& operator=(IntentFactory&&) noexcept = default;

    IntentFactoryRegistrationResult register_builder(const IntentBuilderPtr& builder,
                                                     std::span<const InternedString> key_words);

    /// Create a new instance of an intent based on a keyword
    /// \return null if no matching intent was found
    std::unique_ptr<Intent> create_intent(const InternedString str) const;

   private:
    // Note: std::shared_ptr is a bit overkill here, but sadly c++ does not have a non-atomic
    // reference counted equivalent. There's one in Boost, but don't want to integrate that for
    // this small project.
    using BuilderMap = std::unordered_map<InternedString, IntentBuilderPtr>;
    BuilderMap m_builders;
};

}    // namespace ie