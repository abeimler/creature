#ifndef DATA_FOOD_H_
#define DATA_FOOD_H_

#include "Data/UseItem.h"

namespace data {

BETTER_ENUM(FoodType, size_t, Eat, Drink)

/// Food/Drink Item
class Food : public UseItem {
    private:
    luck_t luck_ = 0.0;
    disc_t disc_ = 0.0;
    hungry_t hungry_ = 0.0;
    thirsty_t thirsty_ = 0.0;
    weight_t weight_ = 0.0;

    calories_t calories_ = 0.0;

    FoodType foodtype_ = FoodType::Eat;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("_base", cereal::base_class<UseItem>(this)));

        ar(cereal::make_nvp("luck", luck_));
        ar(cereal::make_nvp("disc", disc_));
        ar(cereal::make_nvp("hungry", hungry_));
        ar(cereal::make_nvp("thirsty", thirsty_));
        ar(cereal::make_nvp("weight", weight_));

        ar(cereal::make_nvp("calories", calories_));

        ar(cereal::make_nvp("foodtype", foodtype_));
    }


    public:
    Food() = default;

    explicit Food(UseItem item);

    /// Boni for luck
    luck_t getLuck() const { return this->luck_; }

    /// Boni for disciplin
    disc_t getDisc() const { return this->disc_; }

    /// Boni for hungry
    hungry_t getHungry() const { return this->hungry_; }

    /// Boni for thirsty
    thirsty_t getThirsty() const { return this->thirsty_; }

    /// Boni for weight
    weight_t getWeight() const { return this->weight_; }

    /// true, Food-Item is Drinkable
    bool isDrink() const { return this->foodtype_ == +FoodType::Drink; }

    /// true, Food-Item is Eatable
    bool isEat() const { return this->foodtype_ == +FoodType::Eat; }

    /// Boni for calories
    calories_t getCalories() const { return this->calories_; }

    void setLuck(luck_t value) { this->luck_ = value; }

    void setDisc(disc_t value) { this->disc_ = value; }

    void setHungry(hungry_t value) { this->hungry_ = value; }

    void setThirsty(thirsty_t value) { this->thirsty_ = value; }

    void setWeight(weight_t value) { this->weight_ = value; }

    void setFoodType(FoodType type) { this->foodtype_ = type; }

    void setCalories(calories_t value) { this->calories_ = value; }
};

} // namespace data

#endif // DATA_FOOD_H_
