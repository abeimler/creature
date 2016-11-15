#ifndef ENTITY_DATA_DATAMANGER_H_
#define ENTITY_DATA_DATAMANGER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManagerBase.h"

#include "Data/Creature.h"
#include "Data/CreatureBattlerStatus.h"
#include "Data/CreatureType.h"
#include "Data/Element.h"
#include "Data/Food.h"
#include "Data/Skill.h"

namespace gameentity {


class CreatureDataManager : public DataManagerBase<data::Creature> {
    public:
    CreatureDataManager();

    static bool findDataByName(std::string name,
                               const std::shared_ptr<data::Creature>& data) {
        return data && data->getName() == name;
    }

    void save(const data::Creature& data) {
        this->DataManagerBase::save(data.getName(), data);
    }
};

class CreatureBattlerStatusDataManager
    : public DataManagerBase<data::CreatureBattlerStatus> {
    public:
    CreatureBattlerStatusDataManager();

    static bool
    findDataByName(std::string name,
                   const std::shared_ptr<data::CreatureBattlerStatus>& data) {
        return data && data->getName() == name;
    }

    void save(const data::CreatureBattlerStatus& data) {
        this->DataManagerBase::save(data.getName(), data);
    }


    std::shared_ptr<data::CreatureBattlerStatus>
    findByStatus(data::CreatureStatus status) const {
        auto find_func = [status](
            const std::shared_ptr<data::CreatureBattlerStatus>
                creaturebattlerstatus) {
            return creaturebattlerstatus &&
                   creaturebattlerstatus->getCreatureStatus() == status;
        };

        auto it = std::find_if(std::begin(this->data_), std::end(this->data_),
                               find_func);
        return (it != std::end(this->data_)) ? *it : nullptr;
    }
};

class CreatureRootTypeDataManager
    : public DataManagerBase<data::CreatureRootType> {
    public:
    CreatureRootTypeDataManager();

    static bool
    findDataByName(std::string name,
                   const std::shared_ptr<data::CreatureRootType>& data) {
        return data && data->getName() == name;
    }

    void save(const data::CreatureRootType& data) {
        this->DataManagerBase::save(data.getName(), data);
    }


    std::unique_ptr<data::CreatureType>
    findCreatureType(std::string type_name) {
        for (auto& creatureroottype : this->data_) {
            if (creatureroottype) {
                const auto& types = creatureroottype->getTypes();
                auto find_type_it =
                    creatureroottype->findCreatureType(type_name);

                if (find_type_it != std::end(types)) {
                    return std::make_unique<data::CreatureType>(*find_type_it);
                }
            }
        }

        return nullptr;
    }

    const data::CreatureType& saveCreatureType(const data::CreatureType& type) {
        std::string type_name = type.getName();
        std::string creatureroottype_name = type.getCreatureRootType();

        auto creatureroottype = findByName(creatureroottype_name);
        if (creatureroottype) {
            const auto& types = creatureroottype->getTypes();
            auto creaturetype = creatureroottype->findCreatureType(type_name);
            if (creaturetype != std::end(types)) {
                *creaturetype = type;
                return *creaturetype;
            } else {
                return creatureroottype->addCreatureType(type);
            }
        }

        return type;
    }
};


class CreatureStarterDataManager
    : public DataManagerBase<data::CreatureStarter> {
    public:
    CreatureStarterDataManager();

    static bool
    findDataByName(std::string name,
                   const std::shared_ptr<data::CreatureStarter>& data) {
        return data && data->getCreatureName() == name;
    }

    void save(const data::CreatureStarter& data) {
        this->DataManagerBase::save(data.getCreatureName(), data);
    }
};


class ElementDataManager : public DataManagerBase<data::Element> {
    public:
    ElementDataManager();

    static bool findDataByName(std::string name,
                               const std::shared_ptr<data::Element>& data) {
        return data && data->getName() == name;
    }

    void save(const data::Element& data) {
        this->DataManagerBase::save(data.getName(), data);
    }
};


class FoodDataManager : public DataManagerBase<data::Food> {
    public:
    FoodDataManager();

    static bool findDataByName(std::string name,
                               const std::shared_ptr<data::Food>& data) {
        return data && data->getName() == name;
    }

    void save(const data::Food& data) {
        this->DataManagerBase::save(data.getName(), data);
    }
};

class SkillDataManager : public DataManagerBase<data::Skill> {
    public:
    SkillDataManager();

    static bool findDataByName(std::string name,
                               const std::shared_ptr<data::Skill>& data) {
        return data && data->getName() == name;
    }

    void save(const data::Skill& data) {
        this->DataManagerBase::save(data.getName(), data);
    }
};



class DataManager {
    protected:
    CreatureDataManager creatures_;
    CreatureBattlerStatusDataManager creaturebattlerstatuses_;
    CreatureRootTypeDataManager creatureroottypes_;
    CreatureStarterDataManager creaturestarters_;
    ElementDataManager elements_;
    FoodDataManager foods_;
    SkillDataManager skills_;

    public:
    DataManager() = default;

    virtual ~DataManager() = default;
    DataManager(const DataManager&) = default;
    DataManager& operator=(const DataManager&) = default;
    DataManager(DataManager&&) = default;
    DataManager& operator=(DataManager&&) = default;


    std::shared_ptr<data::Element> findElement(std::string name) const {
        return this->elements_.findByName(name);
    }
    void saveElement(const data::Element& data) { this->elements_.save(data); }
    void setElements(const std::vector<std::shared_ptr<data::Element>>& data) {
        this->elements_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::Element>>& getElements() const {
        return this->elements_.getAll();
    }
    ElementDataManager& getElementDataManager() { return this->elements_; }
    const ElementDataManager& getElementDataManager() const {
        return this->elements_;
    }



    std::shared_ptr<data::Creature> findCreature(std::string name) const {
        return this->creatures_.findByName(name);
    }
    void saveCreature(const data::Creature& data) {
        this->creatures_.save(data);
    }
    void
    setCreatures(const std::vector<std::shared_ptr<data::Creature>>& data) {
        this->creatures_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::Creature>>& getCreatures() const {
        return this->creatures_.getAll();
    }
    CreatureDataManager& getCreatureDataManager() { return this->creatures_; }
    const CreatureDataManager& getCreatureDataManager() const {
        return this->creatures_;
    }



    std::shared_ptr<data::CreatureBattlerStatus>
    findCreatureBattlerStatusByStatus(data::CreatureStatus status) const {
        return this->creaturebattlerstatuses_.findByStatus(status);
    }
    std::shared_ptr<data::CreatureBattlerStatus>
    findCreatureBattlerStatus(std::string name) const {
        return this->creaturebattlerstatuses_.findByName(name);
    }
    void saveCreatureBattlerStatus(const data::CreatureBattlerStatus& data) {
        this->creaturebattlerstatuses_.save(data);
    }
    void setCreatureBattlerStatuses(
        const std::vector<std::shared_ptr<data::CreatureBattlerStatus>>& data) {
        this->creaturebattlerstatuses_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::CreatureBattlerStatus>>&
    getCreatureBattlerStatuses() const {
        return this->creaturebattlerstatuses_.getAll();
    }
    CreatureBattlerStatusDataManager& getCreatureBattlerStatusDataManager() {
        return this->creaturebattlerstatuses_;
    }
    const CreatureBattlerStatusDataManager&
    getCreatureBattlerStatusDataManager() const {
        return this->creaturebattlerstatuses_;
    }



    std::shared_ptr<data::CreatureRootType>
    findCreatureRootType(std::string name) const {
        return this->creatureroottypes_.findByName(name);
    }
    void saveCreatureRootType(const data::CreatureRootType& data) {
        this->creatureroottypes_.save(data);
    }
    void setCreatureRootTypes(
        const std::vector<std::shared_ptr<data::CreatureRootType>>& data) {
        this->creatureroottypes_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::CreatureRootType>>&
    getCreatureRootTypes() const {
        return this->creatureroottypes_.getAll();
    }
    CreatureRootTypeDataManager& getCreatureRootTypeDataManager() {
        return this->creatureroottypes_;
    }
    const CreatureRootTypeDataManager& getCreatureRootTypeDataManager() const {
        return this->creatureroottypes_;
    }

    std::unique_ptr<data::CreatureType>
    findCreatureType(std::string type_name) {
        return this->creatureroottypes_.findCreatureType(type_name);
    }

    const data::CreatureType& saveCreatureType(const data::CreatureType& type) {
        return this->creatureroottypes_.saveCreatureType(type);
    }


    std::shared_ptr<data::CreatureStarter>
    findCreatureStarter(std::string name) const {
        return this->creaturestarters_.findByName(name);
    }
    void saveCreatureStarter(const data::CreatureStarter& data) {
        this->creaturestarters_.save(data);
    }
    void setCreatureStarters(
        const std::vector<std::shared_ptr<data::CreatureStarter>>& data) {
        this->creaturestarters_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::CreatureStarter>>&
    getCreatureStarters() const {
        return this->creaturestarters_.getAll();
    }
    CreatureStarterDataManager& getCreatureStarterDataManager() {
        return this->creaturestarters_;
    }
    const CreatureStarterDataManager& getCreatureStarterDataManager() const {
        return this->creaturestarters_;
    }
    void saveCreatureStarter(const data::Creature& data) {
        this->creaturestarters_.save(data::CreatureStarter(data));
    }



    std::shared_ptr<data::Skill> findSkill(std::string name) const {
        return this->skills_.findByName(name);
    }
    void saveSkill(const data::Skill& data) { this->skills_.save(data); }
    void setSkills(const std::vector<std::shared_ptr<data::Skill>>& data) {
        this->skills_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::Skill>>& getSkills() const {
        return this->skills_.getAll();
    }
    SkillDataManager& getSkillDataManager() { return this->skills_; }
    const SkillDataManager& getSkillDataManager() const {
        return this->skills_;
    }



    std::shared_ptr<data::Food> findFood(std::string name) const {
        return this->foods_.findByName(name);
    }
    void saveFood(const data::Food& data) { this->foods_.save(data); }
    void setFoods(const std::vector<std::shared_ptr<data::Food>>& data) {
        this->foods_.setAll(data);
    }
    const std::vector<std::shared_ptr<data::Food>>& getFoods() const {
        return this->foods_.getAll();
    }
    FoodDataManager& getFoodDataManager() { return this->foods_; }
    const FoodDataManager& getFoodDataManager() const { return this->foods_; }
};
}

#endif // ENTITY_DATA_DATAMANGER_H_
