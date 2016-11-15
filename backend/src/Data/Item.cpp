#include "Data/Item.h"

namespace data {

Item::Item(ItemType itype) : price_(0), itype_(std::move(itype)) {}

} // namespace data
