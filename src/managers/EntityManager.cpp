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


#include "EntityManager.h"
#include "ComponentsManager.h"
#include "../entities/HealthIndicator.h"

using namespace Managers;
using namespace Entities;

int EntityManager::mCurrEntityIndex = 1;
std::unordered_map<int, std::shared_ptr<Entities::Entity>> EntityManager::mEntities;

bool EntityManager::destroyEntity(int pId) {
    return mEntities.erase(pId) ? true:false;
}

std::shared_ptr<Entity> EntityManager::getEntity(int pId) {
    auto it = mEntities.find(pId);
    if(it != mEntities.end()){
        return it->second;
    }
    return nullptr;
}

EntityManager::EntityManager() {
    //create Player as id = 1
    createEntity<Player>();
    //create camera
    auto cameraID = createEntity<Entity>();
    Managers::ComponentsManager::createCameraComponent(cameraID);
}
