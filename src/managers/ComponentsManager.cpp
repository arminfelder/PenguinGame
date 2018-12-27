//
// Created by armin on 14.12.18.
//

#include "ComponentsManager.h"

using namespace Managers;
using namespace Components;
using namespace Entities;

std::unordered_map<int, std::shared_ptr<Components::Health>> ComponentsManager::mHealthComponents;
std::unordered_map<int, std::shared_ptr<Components::VisualComponent>> ComponentsManager::mVisualComponents;
std::unordered_map<int, std::shared_ptr<Components::SpatialComponent>> ComponentsManager::mSpatialComponents;


std::unordered_map<int, std::shared_ptr<Components::Health>> &ComponentsManager::getHealthComponents(){

    return mHealthComponents;
}

std::unordered_map<int, std::shared_ptr<Components::VisualComponent>> &ComponentsManager::getVisualComponents(){

    return mVisualComponents;
}

std::unordered_map<int, std::shared_ptr<Components::SpatialComponent>> &ComponentsManager::getSpatialComponents(){

    return mSpatialComponents;
}


bool ComponentsManager::createComponent() {
    return false;
}

void ComponentsManager::createHealthComponent(int pEntityId, int pHp) {
    mHealthComponents.insert({pEntityId, std::make_shared<Health>(pHp)});
}

void ComponentsManager::createVisualComponent(int pEntityId, SDL_Texture* pTexture, int pSizeW, int pSizeH) {
    mVisualComponents.insert({pEntityId, std::make_shared<VisualComponent>(pTexture, pSizeW, pSizeH)});
}

void ComponentsManager::createSpatialComponent(int pEntityId, int pPositionX, int pPositionY) {
    mSpatialComponents.insert({pEntityId, std::make_shared<SpatialComponent>(pPositionX, pPositionY)});
}

std::shared_ptr<Components::Health> &ComponentsManager::getHealthComponent(int pEntityId) {
    return mHealthComponents[pEntityId];
}

std::shared_ptr<Components::VisualComponent> &ComponentsManager::getVisualComponent(int pEntityId) {
    return mVisualComponents[pEntityId];
}

std::shared_ptr<Components::SpatialComponent> &ComponentsManager::getSpatialComponent(int pEntityId) {
    return mSpatialComponents[pEntityId];
}
