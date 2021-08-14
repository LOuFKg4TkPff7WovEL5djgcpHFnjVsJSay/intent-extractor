#pragma once

#include <span.hpp>
#include <tokenizer.hpp>

namespace ie {
    /// Represents a unit of information which can be retrieved from the token list
    class Entity {
    public:
        ~Entity() = default;

        virtual void scan_tokens(const std::size_t intent_location, std::span<Token>) = 0;
    };

}