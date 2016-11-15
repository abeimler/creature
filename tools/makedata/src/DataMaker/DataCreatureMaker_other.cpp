#include "DataMaker/DataCreatureMaker.h"

namespace datamaker {

void DataCreatureMaker::makeElement(std::string name) {
    std::cout << "make element: " << name << '\n';

    data::Element element;
    element.setName(name);
    this->datamanager_.saveElement(element);
}

void DataCreatureMaker::makeElements(const std::vector<std::string>& elements,
                                     const resists_t& resists) {
    for (auto element : elements) {
        makeElement(element);
    }
    this->resists_ = resists;
}



void DataCreatureMaker::initStatuses(CreatureBattlerStatus_map_t& statuses) {
    for (auto index : earr::Enum<data::CreatureStatus>()) {
        if (index == +data::CreatureStatus::Normal) {
            continue;
        }

        auto& status = statuses[+index];
        status.setCreatureStatus(index);
        switch (index) {
            case data::CreatureStatus::Normal:
                break;
            case data::CreatureStatus::Dead:
                status.setName("Dead");
                status.setPriority(100);
                status.setOption(data::StatusOption::Dead, true);
                break;
            case data::CreatureStatus::RunAway:
                status.setName("Run Away");
                status.setPriority(90);
                break;
            case data::CreatureStatus::Sleep:
                status.setName("Sleep");
                status.setPriority(87);
                break;
            case data::CreatureStatus::InHospital:
                status.setName("In Hospital");
                status.setPriority(90);
                break;
            case data::CreatureStatus::RestInHospital:
                status.setName("Rest in Hospital");
                status.setPriority(90);
                break;
            case data::CreatureStatus::Rest:
                status.setName("Rest");
                status.setPriority(87);
                break;
            case data::CreatureStatus::Hurt:
                status.setName("Hurt");
                status.setPriority(86);
                break;
            case data::CreatureStatus::Ill:
                status.setName("Ill");
                status.setPriority(86);
                break;
            case data::CreatureStatus::Training:
                status.setName("Training");
                status.setPriority(91);
                break;
            case data::CreatureStatus::Unhappy:
                status.setName("Unhappy");
                status.setPriority(81);
                break;
            case data::CreatureStatus::Happy:
                status.setName("Happy");
                status.setPriority(81);
                break;
            case data::CreatureStatus::Hungry:
                status.setName("Hungry");
                status.setPriority(83);
                break;
            case data::CreatureStatus::Thirsty:
                status.setName("Thirsty");
                status.setPriority(83);
                break;
            case data::CreatureStatus::Replete:
                status.setName("Replete");
                status.setPriority(80);
                break;
            case data::CreatureStatus::Tired:
                status.setName("Tired");
                status.setPriority(84);
                break;
            case data::CreatureStatus::END:
                break;
        }
    }
}


void DataCreatureMaker::makeStatuses() {
    /*
    Normal = CreatureStatus::STARTCREATURESTATUS,
    Dead, ///< id 0
    RunAway, ///< id 1
    Sleep, ///< id 2
    InHospital, ///< id 3
    RestInHospital, ///< id 4
    Rest, ///< id 5
    Hurt, ///< id 6
    Ill, ///< id 7
    Training, ///< id 8
    Unhappy, ///< id 9
    Happy, ///< id 10
    Hungry, ///< id 11
    Thirsty, ///< id 12
    Replete, ///< id 13
    Tired, ///< id 14
    ENDCREATURESTATUS,
    */

    CreatureBattlerStatus_map_t creaturebattlerstatuses;
    this->initStatuses(creaturebattlerstatuses);

    for (const auto& status : creaturebattlerstatuses) {
        this->datamanager_.saveCreatureBattlerStatus(status.second);
    }


    for (auto index : earr::Enum<data::CreatureStatus>()) {
        if (index == +data::CreatureStatus::Normal) {
            continue;
        }

        auto creaturestatus =
            this->datamanager_.findCreatureBattlerStatusByStatus(index);
        if (!creaturestatus) {
            continue;
        }

        std::string creaturestatus_name = creaturestatus->getName();

        std::vector<data::BattlerStatus> removeStatuses;
        switch (index) {
            case data::CreatureStatus::Normal:
                break;
            case data::CreatureStatus::Dead: {
                for (auto index_j : earr::Enum<data::CreatureStatus>()) {
                    if (index_j == +data::CreatureStatus::Normal) {
                        continue;
                    }
                    if (index_j == index) {
                        continue;
                    }

                    auto remove_creaturestatus =
                        this->datamanager_.findCreatureBattlerStatusByStatus(
                            index_j);
                    if (remove_creaturestatus) {
                        std::string remove_creaturestatus_name =
                            remove_creaturestatus->getName();
                        if (remove_creaturestatus_name != creaturestatus_name) {
                            removeStatuses.emplace_back(*remove_creaturestatus);
                        }
                    }
                }
            } break;
            case data::CreatureStatus::RunAway:
                break;
            case data::CreatureStatus::Sleep:
                break;
            case data::CreatureStatus::InHospital:
                break;
            case data::CreatureStatus::RestInHospital:
                break;
            case data::CreatureStatus::Rest:
                break;
            case data::CreatureStatus::Hurt:
                break;
            case data::CreatureStatus::Ill:
                break;
            case data::CreatureStatus::Training:
                break;
            case data::CreatureStatus::Unhappy: {
                auto remove_creaturestatus =
                    this->datamanager_.findCreatureBattlerStatusByStatus(
                        data::CreatureStatus::Happy);

                if (remove_creaturestatus) {
                    std::string remove_creaturestatus_name =
                        remove_creaturestatus->getName();
                    if (remove_creaturestatus_name != creaturestatus_name) {
                        removeStatuses.emplace_back(*remove_creaturestatus);
                    }
                }
            } break;
            case data::CreatureStatus::Happy: {
                auto remove_creaturestatus =
                    this->datamanager_.findCreatureBattlerStatusByStatus(
                        data::CreatureStatus::Unhappy);

                if (remove_creaturestatus) {
                    std::string remove_creaturestatus_name =
                        remove_creaturestatus->getName();
                    if (remove_creaturestatus_name != creaturestatus_name) {
                        removeStatuses.emplace_back(*remove_creaturestatus);
                    }
                }
            } break;
            case data::CreatureStatus::Hungry: {
                auto remove_creaturestatus =
                    this->datamanager_.findCreatureBattlerStatusByStatus(
                        data::CreatureStatus::Replete);

                if (remove_creaturestatus) {
                    std::string remove_creaturestatus_name =
                        remove_creaturestatus->getName();
                    if (remove_creaturestatus_name != creaturestatus_name) {
                        removeStatuses.emplace_back(*remove_creaturestatus);
                    }
                }
            } break;
            case data::CreatureStatus::Thirsty:
                break;
            case data::CreatureStatus::Replete: {
                auto remove_creaturestatus =
                    this->datamanager_.findCreatureBattlerStatusByStatus(
                        data::CreatureStatus::Hungry);

                if (remove_creaturestatus) {
                    std::string remove_creaturestatus_name =
                        remove_creaturestatus->getName();
                    if (remove_creaturestatus_name != creaturestatus_name) {
                        removeStatuses.emplace_back(*remove_creaturestatus);
                    }
                }
            } break;
            case data::CreatureStatus::Tired:
                break;
            case data::CreatureStatus::END:
                break;
        }


        for (const auto& status : removeStatuses) {
            creaturestatus->addRemoveStatus(status);
        }

        this->datamanager_.saveCreatureBattlerStatus(*creaturestatus);
    }
}


} // namespace datamaker