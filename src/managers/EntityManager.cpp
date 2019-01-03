//
// Created by armin on 14.12.18.
//

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
    auto cameraID = createEntity<Entity>();
    Managers::ComponentsManager::createCameraComponent(cameraID);
}
