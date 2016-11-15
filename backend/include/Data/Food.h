#ifndef DATA_FOOD_H_
#define DATA_FOOD_H_

#include "Data/UseItem.h"

namespace data {

BETTER_ENUM(FoodType, size_t, Eat, Drink)

/// Food/Drink Item
class Food : public UseItem {
    private:
    double luck_ = 0.0;
    double disc_ = 0.0;
    double hungry_ = 0.0;
    double thirsty_ = 0.0;
    double weight_ = 0.0;

    double calories_ = 0.0;

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

    explicit Food(UseItem  item);

    /// Boni for luck
    double getLuck() const { return this->luck_; }

    /// Boni for disciplin
    double getDisc() const { return this->disc_; }

    /// Boni for hungry
    double getHungry() const { return this->hungry_; }

    /// Boni for thirsty
    double getThirsty() const { return this->thirsty_; }

    /// Boni for weight
    double getWeight() const { return this->weight_; }

    /// true, Food-Item is Drinkable
    bool isDrink() const { return this->foodtype_ == +FoodType::Drink; }

    /// true, Food-Item is Eatable
    bool isEat() const { return this->foodtype_ == +FoodType::Eat; }

    /// Boni for calories
    double getCalories() const { return this->calories_; }

    void setLuck(double value) { this->luck_ = value; }

    void setDisc(double value) { this->disc_ = value; }

    void setHungry(double value) { this->hungry_ = value; }

    void setThirsty(double value) { this->thirsty_ = value; }

    void setWeight(double value) { this->weight_ = value; }

    void setFoodType(FoodType type) { this->foodtype_ = type; }

    void setCalories(double value) { this->calories_ = value; }
};

} // namespace data

#endif // DATA_FOOD_H_
