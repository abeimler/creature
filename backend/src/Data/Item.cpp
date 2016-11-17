#include "Data/Item.h"

namespace data {


Item::Item(const Item& baseitem, ItemType itype)
    : Item(baseitem)
{
    this->itype_ = std::move(itype);
}

Item::Item() : itype_(ItemType::Basis) {}

Item::Item(ItemType itype) : price_(0), itype_(std::move(itype)) {}

} // namespace data
