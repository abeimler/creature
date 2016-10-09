#include "UseItem.hpp"

namespace data {

constexpr int UseItem::CANT_USE_ITEM;
constexpr int UseItem::CAN_USE_UNLIMITED;

UseItem::UseItem() : Item(ItemType::UseItem) {
    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attr_, 0);
}

UseItem::UseItem(const Item& item) : Item(item) {
    this->itype_ = ItemType::UseItem;
    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attr_, 0);
}
} // namespace data
