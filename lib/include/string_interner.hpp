#pragma once

#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <unordered_set>

namespace ie {

/// Represents and interned string
class InternedString {
   public:
    InternedString() = default;
    InternedString(const InternedString&) = default;
    InternedString& operator=(const InternedString&) = default;

    inline bool operator==(const InternedString& rhs) const {
        return m_str.data() == rhs.m_str.data();
    }

    inline bool operator!=(const InternedString& rhs) const {
        return m_str.data() != rhs.m_str.data();
    }

    inline explicit operator bool() const { return !m_str.empty(); }

    inline std::string_view view() const { return m_str; }

    friend std::ostream& operator<<(std::ostream& stream, const InternedString& str) {
        stream << str.m_str;
        return stream;
    }

   private:
    friend class StringInterner;
    explicit InternedString(std::string_view str) : m_str(str) {}

   private:
    std::string_view m_str;
};

/// Internalizes strings so that they can be compared via their pointer for equality
class StringInterner {
   public:
    StringInterner() = default;
    StringInterner(const StringInterner&) = delete;
    StringInterner& operator=(const StringInterner&) = delete;
    StringInterner(StringInterner&& rhs) noexcept = default;
    StringInterner& operator=(StringInterner&& rhs) noexcept = default;

    /// Get or internalize the passed in string
    InternedString get_or_intern(const std::string& string);
    InternedString get_or_intern(std::string&& string);
    InternedString get_or_intern(std::string_view string);

   private:
    std::unordered_set<std::string> m_strings;
};
}    // namespace ie

namespace std {
    template<>
    struct hash<ie::InternedString> {
        std::size_t operator()(const ie::InternedString& str) const {
            return std::hash<std::string_view>()(str.view());
        }
    };
    }    // namespace std
