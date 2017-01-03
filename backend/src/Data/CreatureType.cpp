#include "Data/CreatureType.h"

namespace data {

CreatureType::CreatureType(std::string name) : name_(std::move(name)) {}

CreatureRootType::CreatureRootType(std::string name) : name_(std::move(name)) {}

} // namespace data
