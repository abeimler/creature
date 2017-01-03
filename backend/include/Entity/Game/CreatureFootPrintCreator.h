
#ifndef ENTITY_GAME_CREATUREFOOTPRINTCREATOR_H_
#define ENTITY_GAME_CREATUREFOOTPRINTCREATOR_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Component/DateTimer.h"

#include "Component/Game/Battler.h"
#include "Component/Game/Creature.h"

#include "Entity/EntityCreator.h"



namespace gameentity {

    // src: https://github.com/download13/blockies/blob/master/blockies.js
    // alt: https://www.khanacademy.org/computer-programming/github-style-avatar-generator/2762027878
    class BlockiesAsciiCreator {
        public:
        const char* PIXEL_CHAR_VALUE = u8"*";
        const char* PIXEL_CHAR_SPACE = u8" ";
        const char* PIXEL_CHAR_NEWLINE = u8"\n";

        const size_t DEFAULT_SCALE = 1;

        BlockiesAsciiCreator() = default;

        std::vector<std::string> createBlockyArray(std::string seedstr, size_t size, size_t scale);
        std::string createBlockyString(std::string seedstr, size_t size, size_t scale);

        std::vector<std::string> createBlockyArray(std::string seedstr, size_t size) {
            return createBlockyArray(seedstr, size, DEFAULT_SCALE);
        }
        std::string createBlockyString(std::string seedstr, size_t size) {
            return createBlockyString(seedstr, size, DEFAULT_SCALE);
        }
    };

    class CreatureFootPrintCreator {
        private:
        BlockiesAsciiCreator blockiesAsciiCreator_;

        public:
        CreatureFootPrintCreator() = default;

        std::vector<std::string> createPrintArray(std::string creature_name, 
            data::CreatureLevel creature_level,
            data::bodymass_t mass, data::bodysize_t bodysize);
            
        std::string createPrintString(std::string creature_name, 
            data::CreatureLevel creature_level,
            data::bodymass_t mass, data::bodysize_t bodysize);

    };


} // namespace gameentity


#endif // ENTITY_GAME_CREATUREFOOTPRINTCREATOR_H_
