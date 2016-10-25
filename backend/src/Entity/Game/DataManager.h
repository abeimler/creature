#ifndef ENTITY_GAME_DATAMANGER_H_
#define ENTITY_GAME_DATAMANGER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Data/Creature.h"
#include "Data/CreatureBattlerStatus.h"
#include "Data/Element.h"
#include "Data/Skill.h"

namespace gameentity {

class DataManager {
    protected:
    std::vector<std::shared_ptr<data::Skill>> skills_;
    std::vector<std::shared_ptr<data::Element>> elements_;
    std::vector<std::shared_ptr<data::Creature>> creatures_;
    std::vector<std::shared_ptr<data::CreatureBattlerStatus>>
        creaturebattlerstatuses_;

    public:
    DataManager() = default;

    virtual ~DataManager() = default;
    DataManager(const DataManager&) = default;
    DataManager& operator=(const DataManager&) = default;
    DataManager(DataManager&&) = default;
    DataManager& operator=(DataManager&&) = default;



    std::shared_ptr<data::Skill> findSkill(std::string skill_name) const {
        auto find_func =
            [skill_name](const std::shared_ptr<data::Skill>& skill) {
                return skill && skill->getName() == skill_name;
            };

        auto it = std::find_if(std::begin(this->skills_),
                               std::end(this->skills_), find_func);
        return (it != std::end(this->skills_)) ? *it : nullptr;
    }
    void addSkill(const std::shared_ptr<data::Skill>& skill) {
        this->skills_.emplace_back(skill);
    }
    void setSkills(const std::vector<std::shared_ptr<data::Skill>>& skills) {
        this->skills_ = skills;
    }
    const std::vector<std::shared_ptr<data::Skill>>& getSkills() const {
        return this->skills_;
    }



    std::shared_ptr<data::Element> findElement(std::string element_name) const {
        auto find_func =
            [element_name](const std::shared_ptr<data::Element>& element) {
                return element && element->getName() == element_name;
            };

        auto it = std::find_if(std::begin(this->elements_),
                               std::end(this->elements_), find_func);
        return (it != std::end(this->elements_)) ? *it : nullptr;
    }
    void addElement(const std::shared_ptr<data::Element>& element) {
        this->elements_.emplace_back(element);
    }
    void
    setElements(const std::vector<std::shared_ptr<data::Element>>& elements) {
        this->elements_ = elements;
    }
    const std::vector<std::shared_ptr<data::Element>>& getElements() const {
        return this->elements_;
    }



    std::shared_ptr<data::Creature>
    findCreature(std::string creature_name) const {
        auto find_func =
            [creature_name](const std::shared_ptr<data::Creature> creature) {
                return creature && creature->getName() == creature_name;
            };

        auto it = std::find_if(std::begin(this->creatures_),
                               std::end(this->creatures_), find_func);
        return (it != std::end(this->creatures_)) ? *it : nullptr;
    }
    void addCreature(const std::shared_ptr<data::Creature>& creature) {
        this->creatures_.emplace_back(creature);
    }
    void setCreatures(
        const std::vector<std::shared_ptr<data::Creature>>& creatures) {
        this->creatures_ = creatures;
    }
    const std::vector<std::shared_ptr<data::Creature>>& getCreatures() const {
        return this->creatures_;
    }



    std::shared_ptr<data::CreatureBattlerStatus>
    findCreatureBattlerStatus(std::string creaturebattlerstatus_name) const {
        auto find_func = [creaturebattlerstatus_name](
            const std::shared_ptr<data::CreatureBattlerStatus> creature) {
            return creature &&
                   creature->getName() == creaturebattlerstatus_name;
        };

        auto it =
            std::find_if(std::begin(this->creaturebattlerstatuses_),
                         std::end(this->creaturebattlerstatuses_), find_func);
        return (it != std::end(this->creaturebattlerstatuses_)) ? *it : nullptr;
    }
    std::shared_ptr<data::CreatureBattlerStatus>
    findCreatureBattlerStatus(data::CreatureStatus status) const {
        auto find_func = [status](
            const std::shared_ptr<data::CreatureBattlerStatus>
                creaturebattlerstatus) {
            return creaturebattlerstatus &&
                   creaturebattlerstatus->getCreatureStatus() == +status;
        };

        auto it =
            std::find_if(std::begin(this->creaturebattlerstatuses_),
                         std::end(this->creaturebattlerstatuses_), find_func);
        return (it != std::end(this->creaturebattlerstatuses_)) ? *it : nullptr;
    }
    void
    addCreatureBattlerStatus(const std::shared_ptr<data::CreatureBattlerStatus>&
                                 creaturebattlerstatus) {
        this->creaturebattlerstatuses_.emplace_back(creaturebattlerstatus);
    }
    void setCreatureBattlerStatuses(
        const std::vector<std::shared_ptr<data::CreatureBattlerStatus>>&
            creaturebattlerstatuses) {
        this->creaturebattlerstatuses_ = creaturebattlerstatuses;
    }
    const std::vector<std::shared_ptr<data::CreatureBattlerStatus>>&
    getCreatureBattlerStatuses() const {
        return this->creaturebattlerstatuses_;
    }
};
}

#endif // ENTITY_GAME_DATAMANGER_H_