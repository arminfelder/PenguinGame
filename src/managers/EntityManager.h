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


#ifndef GAME_ENTITYMANAGER_H
#define GAME_ENTITYMANAGER_H

#include <memory>
#include <unordered_map>
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Wall.h"
#include "../entities/Ladder.h"

namespace Managers {

    class EntityManager {
    public:
        EntityManager();
        template <class T>
        static int createEntity(){
            int newIndex = mCurrEntityIndex;
            mEntities.emplace(mCurrEntityIndex, std::make_shared<T>(mCurrEntityIndex));
            mCurrEntityIndex++;
            return newIndex;
        }

        static bool destroyEntity(int pId);

        static std::shared_ptr<Entities::Entity> getEntity(int pId);
        static std::shared_ptr<Entities::Entity> findPlayer();
        ~EntityManager();

    private:
        static int mCurrEntityIndex;
        static std::unordered_map<int, std::shared_ptr<Entities::Entity>> mEntities;
    };
}

#endif //GAME_ENTITYMANAGER_H
