#include <intent.hpp>
#include <intent_factory.hpp>
#include <vector>

namespace ie {
IntentFactory::IntentFactory() {}

IntentFactory::~IntentFactory() {}

IntentFactoryRegistrationResult IntentFactory::register_builder(
    StringInterner& interner,
    const std::shared_ptr<IntentBuilder>& builder) {
    const auto keywords = builder->keywords();
    std::vector<InternedString> keywords_interned;
    keywords_interned.reserve(keywords.size());
    // pre validate the existence of the keywords before we insert them
    for (const auto& keyword : keywords) {
        const InternedString keyword_interned = interner.get_or_intern(keyword);
        if (m_builders.find(keyword_interned) != m_builders.end()) {
            return IntentFactoryRegistrationResult::DuplicateKeyWord;
        }
        keywords_interned.push_back(keyword_interned);
    }

    for (const auto& key_word : keywords_interned) {
        m_builders[key_word] = builder;
    }
    return IntentFactoryRegistrationResult::Ok;
}

std::unique_ptr<Intent> IntentFactory::create_intent(const InternedString str) const {
    auto it = m_builders.find(str);
    return it != m_builders.end() ? it->second->create() : nullptr;
}

}    // namespace ie
