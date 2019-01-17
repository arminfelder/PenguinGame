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
std::map<int, std::shared_ptr<Components::Gravity>> ComponentsManager::mGravities;
std::map<int, std::shared_ptr<Components::Momentum>> ComponentsManager::mMomentum;
std::map<int, std::shared_ptr<Components::Path>> ComponentsManager::mPaths;
std::map<int, std::shared_ptr<Components::TimeToLive>> ComponentsManager::mTimeToLives;
std::map<int, std::shared_ptr<Components::CollisionDamage>> ComponentsManager::mDamages;
std::map<int, std::shared_ptr<Components::ViewRange>> ComponentsManager::mViewRanges;
std::map<int, std::shared_ptr<Components::Inventory>> ComponentsManager::mInventories;
std::map<int, std::shared_ptr<Components::CanCollect>> ComponentsManager::mCanCollects;
std::map<int, std::shared_ptr<Components::UseAbel>> ComponentsManager::mUseables;
std::map<int, std::shared_ptr<Components::TeleportTarget>> ComponentsManager::mTeleportTargets;


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
    mHealthComponents.emplace(std::make_pair(pEntityId, std::make_shared<Health>(pHp)));
}

void ComponentsManager::createVisualComponent(int pEntityId, const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH) {
    mVisualComponents.emplace(std::make_pair(pEntityId, std::make_shared<VisualComponent>(pTexture, pSizeW, pSizeH)));
}
void ComponentsManager::createVisualComponent(int pEntityId, const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTextureMap, int pSizeW, int pSizeH) {
    mVisualComponents.emplace(std::make_pair(pEntityId, std::make_shared<VisualComponent>(pTextureMap, pSizeW, pSizeH)));
}


void ComponentsManager::createSpatialComponent(int pEntityId, int pPositionX, int pPositionY,bool pMoveWithMap) {
    mSpatialComponents.emplace(std::make_pair(pEntityId, std::make_shared<SpatialComponent>(pPositionX, pPositionY, pMoveWithMap)));
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
    mMoveableComponents.emplace(std::make_pair(pEntityId,std::make_shared<MoveAbleComponent>(pRight,pDown,pLeft,pUp)));
}

std::map<int, std::shared_ptr<Components::CollideAble>> &ComponentsManager::getCollideAble() {
    return mCollideables;
}

std::shared_ptr<Components::CollideAble> &ComponentsManager::getCollideAble(int pEntityId) {
    return mCollideables[pEntityId];
}

void ComponentsManager::createCollideAbleComponent(int pEntityId) {
    mCollideables.emplace(std::make_pair(pEntityId,std::make_shared<CollideAble>()));
}

std::map<int, std::shared_ptr<Components::CameraOffset>> &ComponentsManager::getCameraOffsets() {
    return mCameraOffset;
}

std::shared_ptr<Components::CameraOffset> &ComponentsManager::getCameraOffsetComponent(int pEntityId) {
    return mCameraOffset[pEntityId];
}

void ComponentsManager::createCameraComponent(int pEntityId) {
    mCameraOffset.emplace(std::make_pair(pEntityId, std::make_shared<CameraOffset>(0, 0)));
}

std::shared_ptr<Components::Momentum> &ComponentsManager::getMomentumComponent(int pEntityId) {
    return mMomentum[pEntityId];
}

void ComponentsManager::createMomentumComponent(int pEntityId) {
    mMomentum.emplace(std::make_pair(pEntityId, std::make_shared<Momentum>()));
}

std::map<int, std::shared_ptr<Components::Momentum>> &ComponentsManager::getMomenta() {
    return mMomentum;
}

std::map<int, std::shared_ptr<Components::Gravity>> &ComponentsManager::getGravities() {
    return mGravities;
}

std::shared_ptr<Components::Gravity> &ComponentsManager::getGravity(int pEntityId) {
    return mGravities[pEntityId];
}

void ComponentsManager::createGravityComponent(int pEntityId) {
    mGravities.emplace(std::make_pair(pEntityId,std::make_shared<Components::Gravity>()));

}

void ComponentsManager::removeComponentsOfEntity(int pEntityId) {
    mHealthComponents.erase(pEntityId);
    mVisualComponents.erase(pEntityId);
    mSpatialComponents.erase(pEntityId);
    mMoveableComponents.erase(pEntityId);
    mCollideables.erase(pEntityId);
    mCameraOffset.erase(pEntityId);
    mGravities.erase(pEntityId);
    mMomentum.erase(pEntityId);
    mPaths.erase(pEntityId);
    mTimeToLives.erase(pEntityId);
    mDamages.erase(pEntityId);
    mViewRanges.erase(pEntityId);
    mInventories.erase(pEntityId);
    mUseables.erase(pEntityId);
}

void ComponentsManager::createPathComponent(int pEntityId, const std::vector<SDL_Point> &pPath, int pStepsPerSecond, bool pRepeat,
                                            bool pRunning) {
    mPaths.emplace(std::make_pair(pEntityId,std::make_shared<Components::Path>(pPath, pStepsPerSecond,pRepeat,pRunning)));
}

std::map<int, std::shared_ptr<Components::Path>> &ComponentsManager::getPaths() {
    return mPaths;
}

std::shared_ptr<Components::Path> &ComponentsManager::getPaths(int pEntityId) {
    return mPaths[pEntityId];
}

std::map<int, std::shared_ptr<Components::CollisionDamage>> &ComponentsManager::getDamages() {
    return mDamages;
}

std::map<int, std::shared_ptr<Components::TimeToLive>> &ComponentsManager::getTimeToLives() {
    return mTimeToLives;
}

std::shared_ptr<Components::CollisionDamage> &ComponentsManager::getDamage(int pEntityId) {
    return mDamages[pEntityId];
}

std::shared_ptr<Components::TimeToLive> &ComponentsManager::getTimeToLive(int pEntityId) {
    return mTimeToLives[pEntityId];
}

void ComponentsManager::createDamageComponent(int pEntityId, int pDamage) {
    mDamages.emplace(std::make_pair(pEntityId, std::make_shared<Components::CollisionDamage>(pDamage)));
}

void ComponentsManager::createTimeToLive(int pEntityId, uint64_t pTime) {
    mTimeToLives.emplace(std::make_pair(pEntityId, std::make_shared<Components::TimeToLive>(pTime)));
}

std::map<int, std::shared_ptr<Components::ViewRange>> &ComponentsManager::getViewRanges() {
    return mViewRanges;
}

std::shared_ptr<Components::ViewRange> &ComponentsManager::getViewRange(int pEntityId) {
    return mViewRanges[pEntityId];
}

void ComponentsManager::createViewRange(int pEntityId, int pX, int pY) {
    mViewRanges.emplace(std::make_pair(pEntityId,std::make_shared<Components::ViewRange>(pX,pY)));
}

std::map<int, std::shared_ptr<Components::Inventory>> &ComponentsManager::getInventories() {
    return mInventories;
}

std::shared_ptr<Components::Inventory> &ComponentsManager::getInventory(int pEntityId) {
    return mInventories[pEntityId];
}

void ComponentsManager::createInventory(int pEntityId) {
    mInventories.emplace(std::make_pair(pEntityId,std::make_shared<Components::Inventory>()));
}

std::map<int, std::shared_ptr<Components::CanCollect>> &ComponentsManager::getCanCollects() {
    return mCanCollects;
}

std::shared_ptr<Components::CanCollect> &ComponentsManager::getCanCollect(int pEntity) {
    return mCanCollects[pEntity];
}

void ComponentsManager::createCanCollect(int pEntityId, const std::set<Components::Inventory::ItemTypes> &pTypes) {
    mCanCollects.emplace(std::make_pair(pEntityId,std::make_shared<Components::CanCollect>(pTypes)));
}

std::map<int, std::shared_ptr<Components::UseAbel>> &ComponentsManager::getUseables() {
    return mUseables;
}

std::shared_ptr<Components::UseAbel> &ComponentsManager::getUseable(int pEntityId) {
    return mUseables[pEntityId];
}

void ComponentsManager::createUseable(int pEntityId, const std::vector<Components::Inventory::ItemTypes> &pTypes) {
    mUseables.emplace(std::make_pair(pEntityId,std::make_shared<Components::UseAbel>(pTypes)));
}

ComponentsManager::~ComponentsManager() {
    mHealthComponents.clear();
    mVisualComponents.clear();
    mSpatialComponents.clear();
    mMoveableComponents.clear();
    mCollideables.clear();
    mCameraOffset.clear();
    mGravities.clear();
    mMomentum.clear();
    mPaths.clear();
    mTimeToLives.clear();
    mDamages.clear();
    mViewRanges.clear();
    mUseables.clear();
    mCanCollects.clear();
    mInventories.clear();
    mTeleportTargets.clear();
}

std::map<int, std::shared_ptr<Components::TeleportTarget>> &ComponentsManager::getTeleportTargets() {
    return mTeleportTargets;
}

std::shared_ptr<Components::TeleportTarget> &ComponentsManager::getTeleportTarget(int pEntityId) {
    return mTeleportTargets[pEntityId];
}

void ComponentsManager::createTeleportTarget(int pEntityId, int pTarget) {
    mTeleportTargets.emplace(std::make_pair(pEntityId,std::make_shared<Components::TeleportTarget>(pTarget)));
}
