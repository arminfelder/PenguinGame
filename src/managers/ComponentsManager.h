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
#include <typeinfo>
#include <typeindex>
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
#include "../components/EvadeCapability.h"

namespace Managers {

    class ComponentsManager {
    public:

        template<typename T>
        static std::map<int, std::shared_ptr<T>> &getComponents() {
            std::map<int, std::shared_ptr<T>> test= std::static_pointer_cast<T> (mComponents[typeid(T)]);
            return test;
        }

        template<typename T>
        static std::shared_ptr<T> &getComponent(int pEntityId) {
            auto retVal =  std::static_pointer_cast<T>(mComponents[typeid(T)][pEntityId]);
            return retVal;
        }

        template <typename T, typename... Args>
        static std::shared_ptr<T> &createComponent(int pEntityId, Args... args) {
            auto pos = mComponents.find(typeid(T));
            if(pos == mComponents.end()){
                mComponents.emplace(std::make_pair(typeid(T),std::map<int, std::shared_ptr<Components::Component>>()));
            }
            mComponents[typeid(T)].emplace(std::make_pair(pEntityId, std::make_shared<T>(args...)));
            return mComponents[typeid(T)][pEntityId];
        }
        static void removeComponentsOfEntity(int pEntityId);
        static void prepareNextMap(std::ostream &out);
        static void saveUserComponents(std::ostream &out);
        static bool loadUserComponents(std::ifstream &inputFile);
        static std::vector<std::string> splitString(const std::string &strToSplit, char delimeter);

        ~ComponentsManager();

    private:

        static std::unordered_map<std::type_index,std::map<int,std::shared_ptr<Components::Component>>> mComponents;

    };
}

#endif //GAME_COMPONENTSMANAGER_H
