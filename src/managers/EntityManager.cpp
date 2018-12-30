//
// Created by armin on 14.12.18.
//

#include "EntityManager.h"

using namespace Managers;
using namespace Entities;

int EntityManager::createEntity() {
    int newIndex = mCurrEntityIndex;
    mEntities.emplace(mCurrEntityIndex, std::make_shared<Entity>(mCurrEntityIndex));
    mCurrEntityIndex++;
    return newIndex;
}

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
    createEntity();
}
