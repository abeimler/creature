#ifndef COMPONENT_TYPES_H_
#define COMPONENT_TYPES_H_

#include "basic.h"

#include "Data/Basic.h"

namespace comp {

using timertime_t = std::chrono::nanoseconds;
using ticks_t = std::chrono::milliseconds;

using time_factor_t = double;

using option_t = data::option_t;
using boolean_t = data::boolean_t;

}

#endif // COMPONENT_TYPES_H_
