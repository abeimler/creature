#ifndef DATA_BASIC_H_
#define DATA_BASIC_H_

// für odb den vollen Pfad mit angeben
#include "basic.h"

#include "Data/BaseModel.h"

/// Einfache Statische Gamedaten
namespace data {

/// Attributes of Hero/Enemy
BETTER_ENUM(Attribute, size_t, BEGIN,
            MaxHP = BEGIN, ///< Maximal HP
            MaxMP,         ///< Minimal MP
            Atk,           ///< Attack
            Def,           ///< Defensive
            Int,           ///< Intelligence
            Agi,           ///< Agility
            Exp,           ///< Experience
            END)

/// Resist of Element
BETTER_ENUM(Resist, size_t, BEGIN,
            MoreSensitivity = BEGIN, ///< double damage, 200%
            Sensitivity,             ///< 1/2 damage more, 150%
            Normal,                  ///< normal damage, 100%
            Resistance,              ///< 1/2 damage less, 50%
            MoreResistance,          ///< 1/4 damage less, 25%
            Immune,                  ///< no damage, 0%
            Heal,                    ///< no damage, heal, -100%
            END)

/// Item Type
BETTER_ENUM(ItemType, size_t, BEGIN,
            Basis = BEGIN, ///< Basis Item
            Weapon,        ///< Weapon Item
            Shield,        ///< Shield (Armor) Item
            Armor,         ///< Armor (Armor) Item
            Helemt,        ///< Helemt (Armor) Item
            Accessory,     ///< Accessory (Armor) Item
            UseItem,       ///< UseItem Item
            END)

/// Target
BETTER_ENUM(TargetOption, size_t, BEGIN,
            None = BEGIN,   ///< None
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

} // namespace data

#endif // DATA_BASIC_H_
