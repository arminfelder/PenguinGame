//
// Created by armin on 14.12.18.
//

#include "ComponentsManager.h"

using namespace Managers;
using namespace Components;
using namespace Entities;

std::map<int, std::shared_ptr<Components::Health>> ComponentsManager::mHealthComponents;
std::map<int, std::shared_ptr<Components::VisualComponent>> ComponentsManager::mVisualComponents;
std::map<int, std::shared_ptr<Components::SpatialComponent>> ComponentsManager::mSpatialComponents;
std::map<int, std::shared_ptr<Components::MoveAbleComponent>> ComponentsManager::mMoveableComponents;
std::map<int, std::shared_ptr<Components::CollideAble>> ComponentsManager::mCollideables;
std::map<int, std::shared_ptr<Components::CameraOffset>> ComponentsManager::mCameraOffset;
std::map<int, std::shared_ptr<Components::Momentum>> ComponentsManager::mMomentum;


std::map<int, std::shared_ptr<Components::Health>> &ComponentsManager::getHealthComponents(){

    return mHealthComponents;
}

std::map<int, std::shared_ptr<Components::VisualComponent>> &ComponentsManager::getVisualComponents(){

    return mVisualComponents;
}

std::map<int, std::shared_ptr<Components::SpatialComponent>> &ComponentsManager::getSpatialComponents(){

    return mSpatialComponents;
}


void ComponentsManager::createHealthComponent(int pEntityId, int pHp) {
    mHealthComponents.insert({pEntityId, std::make_shared<Health>(pHp)});
}

void ComponentsManager::createVisualComponent(int pEntityId, const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH) {
    mVisualComponents.insert({pEntityId, std::make_shared<VisualComponent>(pTexture, pSizeW, pSizeH)});
}
void ComponentsManager::createVisualComponent(int pEntityId, const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTextureMap, int pSizeW, int pSizeH) {
    mVisualComponents.insert({pEntityId, std::make_shared<VisualComponent>(pTextureMap, pSizeW, pSizeH)});
}


void ComponentsManager::createSpatialComponent(int pEntityId, int pPositionX, int pPositionY,bool pMoveWithMap) {
    mSpatialComponents.insert({pEntityId, std::make_shared<SpatialComponent>(pPositionX, pPositionY, pMoveWithMap)});
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

std::map<int, std::shared_ptr<Components::MoveAbleComponent>> &ComponentsManager::getMoveableComponents() {
    return mMoveableComponents;
}

std::shared_ptr<Components::MoveAbleComponent> &ComponentsManager::getMoveableComponent(int pEntityId) {
    return mMoveableComponents[pEntityId];
}

void ComponentsManager::createMoveAbleComponent(int pEntityId, bool pRight, bool pDown, bool pLeft, bool pUp) {
    mMoveableComponents.insert({pEntityId,std::make_shared<MoveAbleComponent>(pRight,pDown,pLeft,pUp)});
}

std::map<int, std::shared_ptr<Components::CollideAble>> &ComponentsManager::getCollideAble() {
    return mCollideables;
}

std::shared_ptr<Components::CollideAble> &ComponentsManager::getCollideAble(int pEntityId) {
    return mCollideables[pEntityId];
}

void ComponentsManager::createCollideAbleComponent(int pEntityId) {
    mCollideables.insert({pEntityId,std::make_shared<CollideAble>()});
}

std::map<int, std::shared_ptr<Components::CameraOffset>> &ComponentsManager::getCameraOffsets() {
    return mCameraOffset;
}

std::shared_ptr<Components::CameraOffset> &ComponentsManager::getCameraOffsetComponent(int pEntityId) {
    return mCameraOffset[pEntityId];
}

void ComponentsManager::createCameraComponent(int pEntityId) {
    mCameraOffset.insert({pEntityId, std::make_shared<CameraOffset>(0, 0)});
}

std::shared_ptr<Components::Momentum> &ComponentsManager::getMomentumComponent(int pEntityId) {
    return mMomentum[pEntityId];
}

void ComponentsManager::createMomentumComponent(int pEntityId) {
    mMomentum.insert({pEntityId, std::make_shared<Momentum>()});
}

std::map<int, std::shared_ptr<Components::Momentum>> &ComponentsManager::getMomentums() {
    return mMomentum;
}
