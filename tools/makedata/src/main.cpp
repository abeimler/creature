#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <json.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>

#include <cxxopts.hpp>

#include "InitData.h"

template <class T>
void saveAsJson(const std::vector<std::shared_ptr<T>>& data,
                std::string filename) {
    std::ofstream os(filename.c_str());
    cereal::JSONOutputArchive archive(os);

    std::vector<T> newdata;
    newdata.reserve(data.size());
    for (const auto& d : data) {
        if (d) {
            newdata.push_back(*d);
        }
    }

    archive(cereal::make_nvp("data", newdata));
}

int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0],
                                 " - creature_makedata command line options");

        options.parse(argc, argv);

        InitData data;

        data.makeDataCreature();

        auto& maker = data.getMaker();
        const auto& datamanager = maker.getDataManager();

        auto elements = datamanager.getElements();
        auto creatures = datamanager.getCreatures();
        auto creaturebattlerstatuses = datamanager.getCreatureBattlerStatuses();
        auto types = datamanager.getCreatureRootTypes();
        auto creaturestarters = datamanager.getCreatureStarters();

        saveAsJson(elements, "elements.json");
        saveAsJson(creatures, "creatures.json");
        saveAsJson(creaturebattlerstatuses, "statuses.json");
        saveAsJson(types, "types.json");
        saveAsJson(creaturestarters, "creaturestarters.json");

    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
