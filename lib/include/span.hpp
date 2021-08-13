#pragma once

// Wrapper header around the std::span type. This type is only available in the C++ 20 standard.

#include <tcb/span.hpp>

namespace std {
template <typename T, std::size_t Extent = tcb::dynamic_extent>
using span = tcb::span<T, Extent>;
}
