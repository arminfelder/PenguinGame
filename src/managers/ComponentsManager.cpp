/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <fstream>
#include <sstream>
#include <iostream>
#include "ComponentsManager.h"

using namespace Managers;
using namespace Components;
using namespace Entities;

std::unordered_map<std::type_index,std::map<int,std::shared_ptr<Components::Component>>> ComponentsManager::mComponents;



void ComponentsManager::removeComponentsOfEntity(int pEntityId) {
    for(auto &entry: mComponents){
        entry.second.erase(pEntityId);
    }
}
/*
void ComponentsManager::addCollectible(int pEntityId, const Components::Inventory::ItemTypes &pType) {
    if (!getCanCollect(pEntityId))
        createCanCollect(pEntityId, {pType});
    else {
        auto collectible = getCanCollect(pEntityId);
        collectible.get()->mTypes.insert(pType);
    }
}*/

ComponentsManager::~ComponentsManager() {
    mComponents.clear();
}


void ComponentsManager::prepareNextMap(std::ostream &out) {
    auto playerHealth = getComponent<Components::Health>(1);
    auto playerInventory = getComponent<Components::Inventory>(1);
    auto playerXP = getComponent<Components::Xp>(1);

    out << playerHealth.get()->serialize() << std::endl;
    out << playerInventory.get()->serialize(); //implicitly returns \n after last element as well
    out << playerXP.get()->serialize() << std::endl;
}

void ComponentsManager::saveUserComponents(std::ostream &out) {
    prepareNextMap(out);
    auto playerPosition = getComponent<SpatialComponent>(1);
    auto playerCamera = getComponent<Components::CameraOffset>(2);
    auto playerMoveAble = getComponent<Components::MoveAbleComponent>(1);
    auto playerMomentum = getComponent<Components::Momentum>(1);
    auto map = getComponent<Components::MapName>(1);

    out << map.get()->serialize() << std::endl;
    out << playerPosition.get()->serialize() << std::endl;
    out << playerCamera.get()->serialize() << std::endl;
    out << playerMoveAble.get()->serialize() << std::endl;
    out << playerMomentum.get()->serialize() << std::endl;
}

bool ComponentsManager::loadUserComponents(std::ifstream &inputFile) {
    //invoke new game to load correct map

    auto playerHealth = getComponent<Components::Health>(1);
    auto playerPosition = getComponent<Components::SpatialComponent>(1);
    auto playerCamera = getComponent<Components::CameraOffset>(2);
    auto playerMoveAble = getComponent<Components::MoveAbleComponent>(1);
    auto playerMomentum = getComponent<Components::Momentum>(1);
    auto playerInventory = getComponent<Components::Inventory>(1);
    auto playerXP = getComponent<Components::Xp>(1);
    auto map = getComponent<Components::MapName>(1);
    playerInventory.get()->reset();

    std::string line;

    bool success = true;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> splittedStrings = splitString(line, ';');

        if (splittedStrings[0] == "Health")
            success = playerHealth.get()->load(splittedStrings);
        else if (splittedStrings[0] == "SpatialComponent")
            success = playerPosition.get()->load(splittedStrings);
        else if (splittedStrings[0] == "CameraOffset")
            success = playerCamera.get()->load(splittedStrings);
        else if (splittedStrings[0] == "MoveAble")
            success = playerMoveAble.get()->load(splittedStrings);
        else if (splittedStrings[0] == "Momentum")
            success = playerMomentum.get()->load(splittedStrings);
        else if (splittedStrings[0] == "Inventory")
            success = playerInventory.get()->load(splittedStrings);
        else if (splittedStrings[0] == "Map")
            success = map.get()->load(splittedStrings);
        else if (splittedStrings[0] == "XP")
            success = playerXP.get()->load(splittedStrings);
        else
            success = false;
        if (!success) {
            std::cout << "Corrupt game file, creating new game" << std::endl;
            return success;
        }
    }
    return success;
}

std::vector<std::string> ComponentsManager::splitString(const std::string &strToSplit, char delimeter) {
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter)) {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}




