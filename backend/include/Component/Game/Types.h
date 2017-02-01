#ifndef COMPONENT_GAME_TYPES_H_
#define COMPONENT_GAME_TYPES_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Component/Types.h"

namespace gamecomp {

using lifetime_t = std::chrono::milliseconds;
using age_t = int;
using birthday_t = std::chrono::system_clock::time_point;
using traintime_t = std::chrono::milliseconds;

using counter_t = unsigned int;

using progresstimer_percent_t = double;
using progresstimer_factor_t = double;
using waittime_t = std::chrono::milliseconds;

template <class T>
using gene_waittime_t = earr::enum_array<T, waittime_t>;

using memory_value_t = int;
using deep_memory_value_t = double;
using memory_factor_t = double;


using option_t = comp::option_t;
using boolean_t = comp::boolean_t;

}

#endif // COMPONENT_GAME_TYPES_H_
