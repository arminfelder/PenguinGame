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
std::map<int, std::shared_ptr<Components::UseAble>> ComponentsManager::mUseables;
std::map<int, std::shared_ptr<Components::TeleportTarget>> ComponentsManager::mTeleportTargets;
std::map<int, std::shared_ptr<Components::MapName>> ComponentsManager::mMapNameComponents;
std::map<int, std::shared_ptr<Components::Xp>> ComponentsManager::mXp;
std::map<int, std::shared_ptr<Components::EvadeCapability>> ComponentsManager::mEvadeCapabilities;
std::map<int, std::shared_ptr<Components::EndsGame>> ComponentsManager::mEndGames;
std::map<int, std::shared_ptr<Components::CanOpen>> ComponentsManager::mCanOpens;
std::map<int, std::shared_ptr<Components::VisitedMaps>> ComponentsManager::mVisitedMaps;
std::map<int, std::shared_ptr<Components::Ownership>> ComponentsManager::mOwnerships;



std::map<int, std::shared_ptr<Components::Health>> &ComponentsManager::getHealthComponents() {

    return mHealthComponents;
}

std::map<int, std::shared_ptr<Components::VisualComponent>> &ComponentsManager::getVisualComponents() {

    return mVisualComponents;
}

std::map<int, std::shared_ptr<Components::SpatialComponent>> &ComponentsManager::getSpatialComponents() {

    return mSpatialComponents;
}


void ComponentsManager::createHealthComponent(int pEntityId, int pHp) {
    mHealthComponents.emplace(std::make_pair(pEntityId, std::make_shared<Health>(pHp)));
}

void ComponentsManager::createVisualComponent(int pEntityId, const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH) {
    mVisualComponents.emplace(std::make_pair(pEntityId, std::make_shared<VisualComponent>(pTexture, pSizeW, pSizeH)));
}

void ComponentsManager::createVisualComponent(int pEntityId,
                                              const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTextureMap,
                                              int pSizeW, int pSizeH) {
    mVisualComponents.emplace(std::make_pair(pEntityId, std::make_shared<VisualComponent>(pTextureMap, pSizeW, pSizeH)));
}


void ComponentsManager::createSpatialComponent(int pEntityId, int pPositionX, int pPositionY, bool pMoveWithMap) {
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
    mMoveableComponents.emplace(std::make_pair(pEntityId, std::make_shared<MoveAbleComponent>(pRight, pDown, pLeft, pUp)));
}

std::map<int, std::shared_ptr<Components::CollideAble>> &ComponentsManager::getCollideAble() {
    return mCollideables;
}

std::shared_ptr<Components::CollideAble> &ComponentsManager::getCollideAble(int pEntityId) {
    return mCollideables[pEntityId];
}

void ComponentsManager::createCollideAbleComponent(int pEntityId) {
    mCollideables.emplace(std::make_pair(pEntityId, std::make_shared<CollideAble>()));
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
    mGravities.emplace(std::make_pair(pEntityId, std::make_shared<Components::Gravity>()));

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
    mTeleportTargets.erase(pEntityId);
    mMapNameComponents.erase(pEntityId);
    mXp.erase(pEntityId);
}

void ComponentsManager::createPathComponent(int pEntityId, const std::vector<SDL_Point> &pPath, int pStepsPerSecond, bool pRepeat,
                                            bool pRunning) {
    mPaths.emplace(std::make_pair(pEntityId, std::make_shared<Components::Path>(pPath, pStepsPerSecond, pRepeat, pRunning)));
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

void ComponentsManager::createTimeToLive(int pEntityId, Uint64 pTime) {
    mTimeToLives.emplace(std::make_pair(pEntityId, std::make_shared<Components::TimeToLive>(pTime)));
}

std::map<int, std::shared_ptr<Components::ViewRange>> &ComponentsManager::getViewRanges() {
    return mViewRanges;
}

std::shared_ptr<Components::ViewRange> &ComponentsManager::getViewRange(int pEntityId) {
    return mViewRanges[pEntityId];
}

void ComponentsManager::createViewRange(int pEntityId, int pX, int pY) {
    mViewRanges.emplace(std::make_pair(pEntityId, std::make_shared<Components::ViewRange>(pX, pY)));
}

std::map<int, std::shared_ptr<Components::Inventory>> &ComponentsManager::getInventories() {
    return mInventories;
}

std::shared_ptr<Components::Inventory> &ComponentsManager::getInventory(int pEntityId) {
    return mInventories[pEntityId];
}

void ComponentsManager::createInventory(int pEntityId) {
    mInventories.emplace(std::make_pair(pEntityId, std::make_shared<Components::Inventory>()));
}

std::map<int, std::shared_ptr<Components::CanCollect>> &ComponentsManager::getCanCollects() {
    return mCanCollects;
}

std::shared_ptr<Components::CanCollect> &ComponentsManager::getCanCollect(int pEntity) {
    return mCanCollects[pEntity];
}

void ComponentsManager::createCanCollect(int pEntityId, const std::set<Components::Inventory::ItemTypes> &pTypes) {
    mCanCollects.emplace(std::make_pair(pEntityId, std::make_shared<Components::CanCollect>(pTypes)));
}

void ComponentsManager::addCollectible(int pEntityId, const Components::Inventory::ItemTypes &pType) {
    if (!getCanCollect(pEntityId))
        createCanCollect(pEntityId, {pType});
    else {
        auto collectible = getCanCollect(pEntityId);
        collectible.get()->mTypes.insert(pType);
    }
}


std::map<int, std::shared_ptr<Components::UseAble>> &ComponentsManager::getUseables() {
    return mUseables;
}

std::shared_ptr<Components::UseAble> &ComponentsManager::getUseable(int pEntityId) {
    return mUseables[pEntityId];
}

void ComponentsManager::createUseable(int pEntityId, const std::vector<Components::Inventory::ItemTypes> &pTypes) {
    mUseables.emplace(std::make_pair(pEntityId, std::make_shared<Components::UseAble>(pTypes)));
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
    mMapNameComponents.clear();
    mXp.clear();
}

std::map<int, std::shared_ptr<Components::TeleportTarget>> &ComponentsManager::getTeleportTargets() {
    return mTeleportTargets;
}

std::shared_ptr<Components::TeleportTarget> &ComponentsManager::getTeleportTarget(int pEntityId) {
    return mTeleportTargets[pEntityId];
}

void ComponentsManager::createTeleportTarget(int pEntityId, int pTarget) {
    mTeleportTargets.emplace(std::make_pair(pEntityId, std::make_shared<Components::TeleportTarget>(pTarget)));
}

std::shared_ptr<Components::MapName> &ComponentsManager::getMapName() {
    return mMapNameComponents[1];
}

void ComponentsManager::createMapName(const std::string &mapName) {
    mMapNameComponents.emplace(std::make_pair(1, std::make_shared<Components::MapName>(Components::MapName(mapName))));
    mVisitedMaps.emplace(std::make_pair(1, std::make_shared<Components::VisitedMaps>(Components::VisitedMaps())));
    mVisitedMaps[1].get()->addMap(mapName);
}

void ComponentsManager::prepareNextMap(std::ostream &out) {
    auto playerHealth = getHealthComponent(1);
    auto playerInventory = getInventory(1);
    auto playerMoveAble = getMoveableComponent(1);
    auto playerXP = getXp(1);

    out << playerHealth.get()->serialize() << std::endl;
    out << playerInventory.get()->serialize(); //implicitly returns \n after last element as well
    out << playerMoveAble.get()->serialize() << std::endl;
    out << playerXP.get()->serialize() << std::endl;
}

void ComponentsManager::saveUserComponents(std::ostream &out) {
    prepareNextMap(out);
    auto playerPosition = getSpatialComponent(1);
    auto playerCamera = getCameraOffsetComponent(2);
    auto playerMomentum = getMomentumComponent(1);
    auto map = getMapName();
    auto visitedMaps = getVisitedMaps();

    out << map.get()->serialize() << std::endl;
    out << playerPosition.get()->serialize() << std::endl;
    out << playerCamera.get()->serialize() << std::endl;
    out << playerMomentum.get()->serialize() << std::endl;
    out << visitedMaps.get()->serialize() << std::endl;
}

bool ComponentsManager::loadUserComponents(std::ifstream &inputFile) {
    //invoke new game to load correct map

    auto playerHealth = getHealthComponent(1);
    auto playerPosition = getSpatialComponent(1);
    auto playerCamera = getCameraOffsetComponent(2);
    auto playerMoveAble = getMoveableComponent(1);
    auto playerMomentum = getMomentumComponent(1);
    auto playerInventory = getInventory(1);
    auto playerXP = getXp(1);
    auto map = getMapName();
    auto visitedMaps = getVisitedMaps();
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
        else if (splittedStrings[0] == "VisitedMaps")
            success = visitedMaps.get()->load(splittedStrings);
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

std::shared_ptr<Components::Xp> &ComponentsManager::getXp(int pEntityId) {
    return mXp[pEntityId];
}

void ComponentsManager::createXp(int pEntityId) {
    mXp.emplace(std::make_pair(pEntityId,std::make_shared<Components::Xp>()));
}

std::map<int, std::shared_ptr<Xp>> &ComponentsManager::getXps() {
    return mXp;
}

std::map<int, std::shared_ptr<EvadeCapability>> &ComponentsManager::getEvadeCapabilities() {
    return mEvadeCapabilities;
}

std::shared_ptr<Components::EvadeCapability> &ComponentsManager::getEvadeCapability(int pEntityId) {
    return mEvadeCapabilities[pEntityId];
}

void ComponentsManager::createEvadeCapability(int pEntityId, int pEvadeChance) {
    mEvadeCapabilities.emplace(std::make_pair(pEntityId, std::make_shared<Components::EvadeCapability>(pEvadeChance)));
}

std::map<int, std::shared_ptr<Components::EndsGame>> &ComponentsManager::getEndGames() {
    return mEndGames;
}

std::shared_ptr<Components::EndsGame> &ComponentsManager::getEndGame(int pEntityId) {
    return mEndGames[pEntityId];
}

void ComponentsManager::createEndGame(int pEntityId) {
    mEndGames.emplace(std::make_pair(pEntityId, std::make_shared<Components::EndsGame>()));
}

std::map<int, std::shared_ptr<Components::CanOpen>> &ComponentsManager::getCanOpens() {
    return mCanOpens;
}

std::shared_ptr<Components::CanOpen> &ComponentsManager::getCanOpen(int pEntityId) {
    return mCanOpens[pEntityId];
}

void ComponentsManager::createCanOpen(int pEntityId, const Components::CanOpen::Areas &pArea) {
    mCanOpens.emplace(std::make_pair(pEntityId,std::make_shared<Components::CanOpen>(pArea)));
}

void ComponentsManager::visitMap(const std::string mapName) {
    mVisitedMaps[1].get()->addMap(mapName);
}

std::shared_ptr<Components::VisitedMaps> &ComponentsManager::getVisitedMaps() {
    return mVisitedMaps[1];
}

std::map<int, std::shared_ptr<Components::Ownership>> &ComponentsManager::getOwnerships() {
    return mOwnerships;
}

std::shared_ptr<Components::Ownership> &ComponentsManager::getOwnership(int pEntityId) {
    return mOwnerships[pEntityId];
}

void ComponentsManager::createOwnership(int pEntityId, int pOwnership) {
    mOwnerships.emplace(std::make_pair(pEntityId, std::make_shared<Components::Ownership>(pOwnership)));
}
