#ifndef DATA_BASIC_H_
#define DATA_BASIC_H_

// für odb den vollen Pfad mit angeben
#include "basic.h"

#include "Data/BaseModel.h"

/// Einfache Statische Gamedaten
namespace data {

/// Attributes of Hero/Enemy
BETTER_ENUM(Attribute, ts::unsigned_t, MaxHP,
            BEGIN = MaxHP, ///< Maximal HP
            MaxMP,         ///< Minimal MP
            Atk,           ///< Attack
            Def,           ///< Defensive
            Int,           ///< Intelligence
            Agi,           ///< Agility
            Exp,           ///< Experience
            END)

/// Resist of Element
BETTER_ENUM(Resist, ts::unsigned_t, MoreSensitivity,
            BEGIN = MoreSensitivity, ///< double damage, 200%
            Sensitivity,             ///< 1/2 damage more, 150%
            Normal,                  ///< normal damage, 100%
            Resistance,              ///< 1/2 damage less, 50%
            MoreResistance,          ///< 1/4 damage less, 25%
            Immune,                  ///< no damage, 0%
            Heal,                    ///< no damage, heal, -100%
            END)

/// Item Type
BETTER_ENUM(ItemType, ts::unsigned_t, Basis,
            BEGIN = Basis, ///< Basis Item
            Weapon,        ///< Weapon Item
            Shield,        ///< Shield (Armor) Item
            Armor,         ///< Armor (Armor) Item
            Helemt,        ///< Helemt (Armor) Item
            Accessory,     ///< Accessory (Armor) Item
            UseItem,       ///< UseItem Item
            END)

/// Target
BETTER_ENUM(TargetOption, ts::unsigned_t, None,
            BEGIN = None,   ///< None
            OneEnemy,       ///< 1 Enemy
            Nenemies,       ///< (Numbers of Atk) enemies
            RandomOneEnemy, ///< 1 Enemy, Random
            RandomNEnemy,   ///< (Numbers of Atk) enemies, Random
            AllEnemies,     ///< All enemies
            OneAlly,        ///< 1 Ally
            Nallies,        ///< (Numbers of Atk) allies
            RandomOneAlly,  ///< 1 All, Random
            RandomNAllies,  ///< (Numbers of Atk) allies, Random
            AllAllies,      ///< All allies
            User,           ///< Self (User)
            END)



using attr_t = ts::int_t;
using lvl_t = ts::int_t;
using percent_rate_t = ts::int_t;
using damage_t = ts::int_t;
using priority_t = ts::int_t;

using turns_t = ts::unsigned_t;
using attr_factor_t = ts::double_t;
using factor_rate_t = ts::double_t;
using noskill_t = ts::int_t;
using sensitivity_t = ts::int_t;

using bmi_t = ts::double_t;
using bodymass_t = ts::double_t;
using weight_t = ts::double_t;
using bodysize_t = ts::double_t;
using luck_t = ts::double_t;
using disc_t = ts::double_t;
using distribution_factor_t = ts::double_t;


using hungry_t = ts::double_t;
using thirsty_t = ts::double_t;
using calories_t = ts::double_t;

using money_t = ts::int_t;

using item_use_t = ts::int_t;
using atknumbers_t = ts::int_t;

using option_t = ts::bool_t;

} // namespace data

#endif // DATA_BASIC_H_
