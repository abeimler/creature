#include "enum_array.h"

namespace earr {

template <class E>
constexpr size_t Enum<E>::begin_enum;

template <class E>
constexpr size_t Enum<E>::end_enum;

template <class E>
constexpr size_t Enum<E>::count;
} // namespace earr