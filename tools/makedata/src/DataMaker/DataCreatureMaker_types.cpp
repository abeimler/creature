#include "DataMaker/DataCreatureMaker.h"

namespace datamaker {

void DataCreatureMaker::makeRootType(std::string name) {
    auto find_roottype = this->datamanager_.findCreatureRootType(name);
    if (!find_roottype) {
        std::cout << "make root type: " << name << '\n';
        data::CreatureRootType data;
        data.setName(name);

        std::cout << "save root type: " << name << '\n';
        this->datamanager_.saveCreatureRootType(data);
    }
}

void DataCreatureMaker::makeType(std::string name, std::string root_name) {
    std::cout << "make type: " << name << " (" << root_name << ")" << '\n';

    makeRootType(root_name);

    auto find_roottype = this->datamanager_.findCreatureRootType(root_name);
    if (find_roottype) {
        if (!find_roottype->isExistCreatureType(name)) {
            data::CreatureType data;
            data.setName(name);

            std::cout << "add type: " << name << '\n';
            find_roottype->addCreatureType(data);
        }

        std::cout << "save root type: " << name << '\n';
        this->datamanager_.saveCreatureRootType(*find_roottype);
    }
}

void DataCreatureMaker::makeTypes(
    const std::map<std::string, std::vector<std::string>>& types) {
    for (auto& type : types) {
        std::string root_type_name = type.first;

        for (std::string sub_type : type.second) {
            makeType(sub_type, root_type_name);
        }
    }
}


} // namespace datamaker