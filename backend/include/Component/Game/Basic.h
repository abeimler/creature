#ifndef COMPONENT_GAME_BASIC_H_
#define COMPONENT_GAME_BASIC_H_

#include "Data/Basic.h"

#include "Component/Basic.h"

namespace gamecomp {
    
namespace ts = type_safe;

using lifetime_t = std::chrono::milliseconds;
using age_t = ts::int_t;
using birthday_t = std::chrono::system_clock::time_point;
using traintime_t = std::chrono::milliseconds;

using counter_t = ts::unsigned_t;

using progresstimer_percent_t = ts::double_t;
using progresstimer_factor_t = ts::double_t;
using waittime_t = std::chrono::milliseconds;

template <class T>
using gene_waittime_t = earr::enum_array<T, waittime_t>;

} // namespace gamecomp


#endif // COMPONENT_GAME_BASIC_H_
