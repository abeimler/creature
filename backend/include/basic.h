#ifndef BASIC_H_
#define BASIC_H_


// stl c libs
#include <cmath>
#include <cstdint>
#include <ctime>

// stl types/container
#include <array>
#include <chrono>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <clamp.hpp>

#include <type_safe/narrow_cast.hpp> // narrow_cast<>
#include <type_safe/types.hpp>       // boolean<>, integer<>, floating_point<>, aliases
#include <type_safe/optional.hpp>
#include <type_safe/optional_ref.hpp>
#include <type_safe/visitor.hpp>
#include <type_safe/output_parameter.hpp>

// custom basic libs
#include "dateutil.h"
#include "enum_array.h"
#include "util.h"

#endif // BASIC_H_
