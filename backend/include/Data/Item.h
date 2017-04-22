#ifndef DATA_ITEM_H_
#define DATA_ITEM_H_

#include "Data/Basic.h"

namespace data {

/// Basis Item Class
class Item {
    private:
    std::string name_;

    std::string icon_filename_;
    std::string description_;

    money_t price_ = 0;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("name", name_));
        ar(cereal::make_nvp("icon_filename", icon_filename_));
        ar(cereal::make_nvp("description", description_));
        ar(cereal::make_nvp("price", price_));
    }


    protected:
    /// item type (UseItem, Weapon, Armor, ...)
    ItemType itype_;

    explicit Item(ItemType itype);
    explicit Item(Item baseitem, ItemType itype_);

  public:
    Item();

    virtual ~Item() = default;
    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    Item(Item&&) = default;
    Item& operator=(Item&&) = default;

    /// Item-Type (Weapon,Armor,Shield,...)
    ItemType getItemType() const { return this->itype_; }

    /// Name
    std::string getName() const { return this->name_; }

    /// Icon Filename
    std::string getIconFilename() { return this->icon_filename_; }

    /// Description
    std::string getDescription() { return this->description_; }

    /// Price
    money_t getPrice() { return this->price_; }

    void setName(std::string name) { this->name_ = name; }

    void setIconFilename(std::string filename) {
        this->icon_filename_ = filename;
    }

    void setDescription(std::string description) {
        this->description_ = description;
    }

    void setPrice(money_t price) { this->price_ = price; }
};

} // namespace data

#endif // DATA_ITEM_H_
