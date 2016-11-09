#include "Entity/Game/CreatureEntityCreator.h"

namespace gameentity {

gamecomp::CreatureMemoryComponent CreatureEntityCreator::createCreatureMemory() {
    gamecomp::CreatureMemoryComponent ret;

    int variance = util::random(-this->max_short_memorysize_variance_,
                          this->max_short_memorysize_variance_);

    int memorySize = static_cast<int>(this->max_short_memorysize_) + variance;

    ret.max_short_memorysize = (memorySize >= 0)
                                   ? static_cast<size_t>(memorySize)
                                   : this->max_short_memorysize_;

    ret.short_memory.clear();
    ret.deep_memory.clear();

    return ret;
}

} // namespace gameentity
