#include "Data/UseItem.h"

namespace data {

constexpr item_use_t UseItem::CANT_USE_ITEM;
constexpr item_use_t UseItem::CAN_USE_UNLIMITED;
constexpr item_use_t UseItem::CAN_USE_ITEM_ONCE;

UseItem::UseItem() : Item(ItemType::UseItem) {
    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attr_, 0);
}

UseItem::UseItem(Item item) : Item(std::move(item), ItemType::UseItem) {
    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attr_, 0);
}
} // namespace data
