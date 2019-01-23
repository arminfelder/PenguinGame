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


#ifndef GAME_COMPONENTSMANAGER_H
#define GAME_COMPONENTSMANAGER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include "../components/Component.h"
#include "../components/Health.h"
#include "../components/Position.h"
#include "../entities/Entity.h"
#include "../components/VisualComponent.h"
#include "../components/SpatialComponent.h"
#include "../components/MoveAbleComponent.h"
#include "../components/CollideAble.h"
#include "../components/CameraOffset.h"
#include "../components/Momentum.h"
#include "../components/Gravity.h"
#include "../components/Path.h"
#include "../components/CollisionDamage.h"
#include "../components/TimeToLive.h"
#include "../components/ViewRange.h"
#include "../components/Inventory.h"
#include "../components/CanCollect.h"
#include "../components/UseAbel.h"
#include "../components/TeleportTarget.h"
#include "../components/MapName.h"
#include "../components/Xp.h"

namespace Managers {

    class ComponentsManager {
    public:
        //TODO: use template functions
        static std::map<int, std::shared_ptr<Components::Health>> &getHealthComponents();
        static std::map<int, std::shared_ptr<Components::VisualComponent>> &getVisualComponents();
        static std::map<int, std::shared_ptr<Components::SpatialComponent>> &getSpatialComponents();
        static std::map<int, std::shared_ptr<Components::MoveAbleComponent>> &getMoveableComponents();
        static std::map<int, std::shared_ptr<Components::CollideAble>> &getCollideAble();
        static std::map<int, std::shared_ptr<Components::CameraOffset>> &getCameraOffsets();
        static std::map<int, std::shared_ptr<Components::Gravity>> &getGravities();
        static std::map<int, std::shared_ptr<Components::Momentum>> &getMomenta();
        static std::map<int, std::shared_ptr<Components::Path>> &getPaths();
        static std::map<int, std::shared_ptr<Components::CollisionDamage>> &getDamages();
        static std::map<int, std::shared_ptr<Components::TimeToLive>> &getTimeToLives();
        static std::map<int, std::shared_ptr<Components::ViewRange>> &getViewRanges();
        static std::map<int, std::shared_ptr<Components::Inventory>> &getInventories();
        static std::map<int, std::shared_ptr<Components::CanCollect>> &getCanCollects();
        static std::map<int, std::shared_ptr<Components::UseAbel>> &getUseables();
        static std::map<int, std::shared_ptr<Components::TeleportTarget>> &getTeleportTargets();
        static std::map<int, std::shared_ptr<Components::Xp>> &getXps();

        static std::shared_ptr<Components::Health> &getHealthComponent(int pEntityId);
        static std::shared_ptr<Components::VisualComponent> &getVisualComponent(int pEntityId);
        static std::shared_ptr<Components::SpatialComponent> &getSpatialComponent(int pEntityId);
        static std::shared_ptr<Components::MoveAbleComponent> &getMoveableComponent(int pEntityId);
        static std::shared_ptr<Components::CollideAble> &getCollideAble(int pEntityId);
        static std::shared_ptr<Components::CameraOffset> &getCameraOffsetComponent(int pEntityId);
        static std::shared_ptr<Components::Gravity> &getGravity(int pEntityId);
        static std::shared_ptr<Components::Momentum> &getMomentumComponent(int pEntityId);
        static std::shared_ptr<Components::Path> &getPaths(int pEntityId);
        static std::shared_ptr<Components::CollisionDamage> &getDamage(int pEntityId);
        static std::shared_ptr<Components::TimeToLive> &getTimeToLive(int pEntityId);
        static std::shared_ptr<Components::ViewRange> &getViewRange(int pEntityId);
        static std::shared_ptr<Components::Inventory> &getInventory(int pEntityId);
        static std::shared_ptr<Components::CanCollect> &getCanCollect(int pEntityId);
        static std::shared_ptr<Components::UseAbel> &getUseable(int pEntityId);
        static std::shared_ptr<Components::TeleportTarget> &getTeleportTarget(int pEntityId);
        static std::shared_ptr<Components::MapName> &getMapName();
        static std::shared_ptr<Components::Xp> &getXp(int pEntityId);

        static void createHealthComponent(int pEntityId, int pHp = 100);
        static void createVisualComponent(int pEntityId, const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH);
        static void createVisualComponent(int pEntityId, const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTextureMap, int pSizeW, int pSizeH);
        static void createSpatialComponent(int pEntityId, int pPositionX, int pPositionY,bool pMoveWithMap = true);
        static void createMoveAbleComponent(int pEntityId, bool pRight, bool pDown, bool pLeft, bool pUp);
        static void createCollideAbleComponent(int pEntityId);
        static void createCameraComponent(int pEntityId);
        static void createGravityComponent(int pEntityId);
        static void createMomentumComponent(int pEntityId);
        static void createPathComponent(int pEntityId, const std::vector<SDL_Point> &pPath, int pStepsPerSecond, bool pRepeat = true, bool pRunning = true);
        static void createDamageComponent(int pEntityId, int pDamage);
        static void createTimeToLive(int pEntityId, uint64_t pTime);
        static void createViewRange(int pEntityId, int pX, int pY);
        static void createInventory(int pEntityId);
        static void createCanCollect(int pEntityId, const std::set<Components::Inventory::ItemTypes> &pTypes);
        static void addCollectible(int pEntityId, const Components::Inventory::ItemTypes &pType);
        static void createUseable(int pEntityId, const std::vector<Components::Inventory::ItemTypes> &pTypes);
        static void createTeleportTarget(int pEntityId, int pTarget);
        static void createMapName(const std::string &mapName);
        static void createXp(int pEntityId);

        static void removeComponentsOfEntity(int pEntityId);
        static void prepareNextMap(std::ostream &out);
        static void saveUserComponents(std::ostream &out);
        static bool loadUserComponents(std::ifstream &inputFile);
        static std::vector<std::string> splitString(const std::string &strToSplit, char delimeter);

        ~ComponentsManager();

    private:
        //TODO: use a container for the maps
        static std::map<int, std::shared_ptr<Components::Health>> mHealthComponents;
        static std::map<int, std::shared_ptr<Components::VisualComponent>> mVisualComponents;
        static std::map<int, std::shared_ptr<Components::SpatialComponent>> mSpatialComponents;
        static std::map<int, std::shared_ptr<Components::MoveAbleComponent>> mMoveableComponents;
        static std::map<int, std::shared_ptr<Components::CollideAble>> mCollideables;
        static std::map<int, std::shared_ptr<Components::CameraOffset>> mCameraOffset;
        static std::map<int, std::shared_ptr<Components::Gravity>> mGravities;
        static std::map<int, std::shared_ptr<Components::Momentum>> mMomentum;
        static std::map<int, std::shared_ptr<Components::Path>> mPaths;
        static std::map<int, std::shared_ptr<Components::TimeToLive>> mTimeToLives;
        static std::map<int, std::shared_ptr<Components::CollisionDamage>> mDamages;
        static std::map<int, std::shared_ptr<Components::ViewRange>> mViewRanges;
        static std::map<int, std::shared_ptr<Components::Inventory>> mInventories;
        static std::map<int, std::shared_ptr<Components::CanCollect>> mCanCollects;
        static std::map<int, std::shared_ptr<Components::UseAbel>> mUseables;
        static std::map<int, std::shared_ptr<Components::TeleportTarget>> mTeleportTargets;
        static std::map<int, std::shared_ptr<Components::MapName>> mMapNameComponents;
        static std::map<int, std::shared_ptr<Components::Xp>> mXp;


    };
}

#endif //GAME_COMPONENTSMANAGER_H
