#include <intent.hpp>
#include <intent_factory.hpp>

namespace ie {
IntentFactory::IntentFactory() {}

IntentFactory::~IntentFactory() {}

IntentFactoryRegistrationResult IntentFactory::register_builder(
    const std::shared_ptr<IntentBuilder>& builder,
    std::span<const InternedString> key_words) {
    // pre validate the existence of the keywords before we insert them
    for (const auto& key_word : key_words) {
        if (m_builders.find(key_word) != m_builders.end()) {
            return IntentFactoryRegistrationResult::DuplicateKeyWord;
        }
    }

    for (const auto& key_word : key_words) {
        m_builders[key_word] = builder;
    }
    return IntentFactoryRegistrationResult::Ok;
}

std::unique_ptr<Intent> IntentFactory::create_intent(const InternedString str) const {
    auto it = m_builders.find(str);
    return it != m_builders.end() ? it->second->create() : nullptr;
}

}    // namespace ie
