#ifndef COMPONENT_GAME_BASIC_H_
#define COMPONENT_GAME_BASIC_H_

#include "Data/Basic.h"

#include "Component/Basic.h"

namespace gamecomp {

using lifetime_t = std::chrono::milliseconds;
using age_t = int;
using birthday_t = std::chrono::system_clock::time_point;
using traintime_t = std::chrono::milliseconds;

using counter_t = int;

using progresstimer_percent_t = double;
using progresstimer_factor_t = double;
using waittime_t = std::chrono::milliseconds;

template <class T>
using gene_waittime_t = earr::enum_array<T, waittime_t>;

} // namespace gamecomp


#endif // COMPONENT_GAME_BASIC_H_
