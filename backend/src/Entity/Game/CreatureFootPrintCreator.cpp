#include "Entity/Game/CreatureFootPrintCreator.h"

namespace gameentity {

std::vector<std::string> BlockiesAsciiCreator::createBlockyArray(std::string seedstr, size_t size, size_t scale) {
    auto width = size;
    auto height = size;

    auto gen = util::genseed(seedstr);

    auto dataWidth = ceil(width / 2);
    auto mirrorWidth = width - dataWidth; 

    std::vector<std::string> data;
    data.reserve(height);
    for(size_t y = 0; y < height; y++) {
        std::string row;
        row.reserve(dataWidth);
        for(size_t x = 0; x < dataWidth; x++) {
            auto s = (util::rand(gen) >= 0.5)? PIXEL_CHAR_VALUE : PIXEL_CHAR_SPACE;
            for(size_t xx = 0;xx < scale; xx++) {
                row.append(s);
            }
        }

        auto r = row.substr(0, mirrorWidth);
        std::reverse(std::begin(r), std::end(r));
        row.append(r);
        
        for(size_t yy = 0; yy < scale; yy++) {
            data.push_back(row);
        }
    }

    return data;
}

std::string BlockiesAsciiCreator::createBlockyString(std::string seedstr, size_t size, size_t scale) {
    auto data = createBlockyArray(seedstr, size, scale);

    std::string ret; 

    // width * height + newlines
    ret.reserve(size * size + size);

    for(auto d : data) {
        ret.append(d);
        ret.append(PIXEL_CHAR_NEWLINE);
    }

    return ret;
}

std::vector<std::string> CreatureFootPrintCreator::createPrintArray(std::string creature_name, data::CreatureLevel creature_level, 
    data::bodymass_t mass, data::bodysize_t bodysize) {

    auto size = (2 + creature_level._to_integral()) + ((100.0 / mass)/1000.0);
    auto scale = 1 + bodysize;

    return blockiesAsciiCreator_.createBlockyArray(creature_name, size, scale);
}

std::string CreatureFootPrintCreator::createPrintString(std::string creature_name, data::CreatureLevel creature_level, 
    data::bodymass_t mass, data::bodysize_t bodysize) {
    
    auto size = (2 + creature_level._to_integral()) + ((100.0 / mass)/1000.0);
    auto scale = 1 + bodysize;

    return blockiesAsciiCreator_.createBlockyString(creature_name, size, scale);
}


} // namespace gameentity
