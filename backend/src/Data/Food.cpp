#include "Data/Food.h"

namespace data {

Food::Food(UseItem item) : UseItem(std::move(item)) {}

} // namespace data
