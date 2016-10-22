#ifndef ENUM_ARRAY_H_
#define ENUM_ARRAY_H_


// stl c libs
#include <cstdint>

// stl types/container
#include <array>
#include <memory>
#include <string>

#include <type_traits>

#include <cereal/cereal.hpp>
#include <cereal/macros.hpp>
#include <cereal/types/array_fixed.hpp>
#include <cereal/types/string.hpp>

#ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
#define BETTER_ENUMS_CONSTEXPR_TO_STRING
#endif

#define BETTER_ENUMS_DEFAULT_CONSTRUCTOR(Enum)                           \
    public:                                                              \
    Enum() = default;                                                    \
    template <class Archive,                                             \
              cereal::traits::EnableIf<cereal::traits::is_text_archive<  \
                  Archive>::value> = cereal::traits::sfinae>             \
    std::string save_minimal(Archive&) const {                           \
        return _to_string();                                             \
    }                                                                    \
    template <class Archive,                                             \
              cereal::traits::EnableIf<cereal::traits::is_text_archive<  \
                  Archive>::value> = cereal::traits::sfinae>             \
    void load_minimal(Archive const&, std::string const& str) {          \
        _value = _from_string(str.c_str())._to_integral();               \
    }                                                                    \
    template <class Archive,                                             \
              cereal::traits::DisableIf<cereal::traits::is_text_archive< \
                  Archive>::value> = cereal::traits::sfinae>             \
    _integral save_minimal(Archive&) const {                             \
        return _value;                                                   \
    }                                                                    \
    template <class Archive,                                             \
              cereal::traits::DisableIf<cereal::traits::is_text_archive< \
                  Archive>::value> = cereal::traits::sfinae>             \
    void load_minimal(Archive const&, _integral const& xx) {             \
        _value = xx;                                                     \
    }


/*
    template <class Archive>                                                   \
    inline                                                                     \
        typename std::enable_if<cereal::traits::is_output_serializable<        \
                                    cereal::BinaryData<Enum>, Archive>::value, \
                                void>::type                                    \
        CEREAL_SAVE_FUNCTION_NAME(Archive& ar) const {                         \
        ar(_value);                                                            \
    }                                                                          \
    template <class Archive>                                                   \
    inline                                                                     \
        typename std::enable_if<cereal::traits::is_input_serializable<         \
                                    cereal::BinaryData<Enum>, Archive>::value, \
                                void>::type                                    \
        CEREAL_LOAD_FUNCTION_NAME(Archive& ar) {                               \
        ar(_value);                                                            \
    }                                                                          \
    template <class Archive>                                                   \
    inline                                                                     \
        typename std::enable_if<!cereal::traits::is_output_serializable<       \
                                    cereal::BinaryData<Enum>, Archive>::value, \
                                void>::type                                    \
        CEREAL_SAVE_FUNCTION_NAME(Archive& ar) const {                         \
        std::string estr = _to_string();                                       \
        ar(estr);                                                              \
    }                                                                          \
    template <class Archive>                                                   \
    inline                                                                     \
        typename std::enable_if<!cereal::traits::is_input_serializable<        \
                                    cereal::BinaryData<Enum>, Archive>::value, \
                                void>::type                                    \
        CEREAL_LOAD_FUNCTION_NAME(Archive& ar) {                               \
        std::string estr;                                                      \
        ar(estr);                                                              \
        _value = _from_string(estr.c_str())._to_integral();                    \
    }
*/

#include <better-enums/n4428.h>
#include <enum.h>



namespace earr {
/**
 * Enum Array
 */
template <class E>
class Enum {
    public:
    // static_assert(std::is_enum<E>::value, "E must be anum");

    /*
    using underlying_type = typename std::underlying_type<E>::type;
    static_assert(std::is_unsigned<underlying_type>::value,
                  "underlying_type of E must be unsigned");
    */

    using underlying_type = size_t;

    static constexpr size_t begin_enum = static_cast<size_t>(E::BEGIN);
    static constexpr size_t end_enum = static_cast<size_t>(E::END);
    static constexpr size_t count =
        (end_enum - begin_enum < end_enum) ? end_enum : end_enum - begin_enum;

    template <class T>
    using array = std::array<T, count>;

    static size_t to_index(E index) noexcept {
        return static_cast<size_t>(index);
    }
    static E to_enum(underlying_type index) noexcept {
        return static_cast<E>(index);
    }

    template <class T>
    static const T& array_at(const array<T>& arr, E index) noexcept {
        return arr[to_index(index)];
    }
    template <class T>
    static T& array_at(array<T>& arr, E index) noexcept {
        return arr[to_index(index)];
    }

    template <class T>
    static typename array<T>::const_iterator array_at_it(const array<T>& arr,
                                                         E index) {
        return arr.cbegin() + to_index(index);
    }
    template <class T>
    static typename array<T>::iterator array_at_it(array<T>& arr, E index) {
        return arr.begin() + to_index(index);
    }

    class EnumIterator {
        private:
        underlying_type m_value;

        public:
        explicit EnumIterator(const underlying_type& value) : m_value(value) {}

        E operator*(void)const noexcept { return static_cast<E>(m_value); }

        void operator++(void)noexcept { ++m_value; }

        bool operator!=(const EnumIterator& rhs) noexcept {
            return m_value != rhs.m_value;
        }
    };

    Enum() = default;

    EnumIterator begin() const {
        // avoid linking error, undefined reference begin_enum
        static constexpr underlying_type b = Enum<E>().begin_enum;
        return EnumIterator(b);
    }
    EnumIterator end() const {
        // avoid linking error, undefined reference end_enum
        static constexpr underlying_type e = Enum<E>().end_enum;
        return EnumIterator(e);
    }
};

template <class E, class T>
using enum_array = std::array<T, Enum<E>::count>;

template <class E, class T>
inline T& enum_array_at(enum_array<E, T>& arr, E index) noexcept {
    return Enum<E>::array_at(arr, index);
}
template <class E, class T>
inline const T& enum_array_at(const enum_array<E, T>& arr, E index) noexcept {
    return Enum<E>::array_at(arr, index);
}

template <class E, class T>
inline typename enum_array<E, T>::iterator
enum_array_at_it(enum_array<E, T>& arr, E index) {
    return Enum<E>::array_at_it(arr, index);
}
template <class E, class T>
inline typename enum_array<E, T>::const_iterator
enum_array_at_it(const enum_array<E, T>& arr, E index) {
    return Enum<E>::array_at_it(arr, index);
}

template <class E, class T>
inline void enum_array_set(enum_array<E, T>& arr, E index, const T& value) {
    Enum<E>::array_at(arr, index) = value;
}

template <class E, class T, class... Args>
inline void enum_array_set(enum_array<E, T>& arr, E index, Args&&... args) {
    Enum<E>::array_at(arr, index) = T(std::forward<Args>(args)...);
}


template <class E, class T>
inline size_t enum_to_index(const enum_array<E, T>& /*arr*/, E index) noexcept {
    return Enum<E>::to_index(index);
}

template <class E>
inline size_t enum_to_index(E index) noexcept {
    return Enum<E>::to_index(index);
}

/*
// couldn't deduce template parameter ‘E’
template <class E, class T>
inline E index_to_enum(const enum_array<E, T>& arr, size_t index) noexcept {
    return Enum<E>::to_enum(index);
}
*/

template <class E, class T>
inline void enum_array_fill(enum_array<E, T>& arr, const T& value) {
    std::fill(std::begin(arr), std::end(arr), value);
}

template <class T, size_t N>
inline void enum_array_fill(std::array<T, N>& arr, const T& value) {
    std::fill(std::begin(arr), std::end(arr), value);
}
}

#endif // ENUM_ARRAY_H_
