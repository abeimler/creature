#include "InitData.h"

InitData::InitData() {}

void InitData::makeDataCreature() {
    this->initElements();
    this->initTypes();

    this->maker_.initBeforData(this->elements_, this->elements_resists_,
                               this->types_);

    this->makeCreature1();
    this->makeCreature2();

    this->updateCreature1();
    this->updateCreature2();

    this->maker_.initAfterData();
}
