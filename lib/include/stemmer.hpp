#pragma once

#include <memory>
#include <string>

namespace ie {
class Stemmer {
   public:
    virtual ~Stemmer() = default;
    /// Stem the input and return true whether modifications were made, false otherwise
    virtual bool stem(std::string&) = 0;
};

class DefaultStemmer final : public Stemmer {
   public:
    bool stem(std::string& string) override;
};
}    // namespace ie