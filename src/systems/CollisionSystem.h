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

#ifndef GAME_COLLISIONSYSTEM_H
#define GAME_COLLISIONSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"
#include "../events/CollisionEvent.h"
#include "../components/CollideAble.h"

namespace Systems {
    class CollisionSystem: public System {
    public:
        CollisionSystem(Managers::EventsManager *pEventsmanager);
        void changeCollisionMask(std::vector<bool> *collisionMask);
        void changeMapWidth(int width);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        std::vector<bool> *collisionMask = nullptr;
        int mapWidth = -1;
        bool detectCollision(int topLimit, int entryTopLimit, int bottomLimit, int entryBottomLimit, int entityId, Events::collisionTypes collisionType, const std::pair<int, std::shared_ptr<Components::CollideAble>> entry, Managers::EventsManager* mEventsManager);

    };
}


#endif //GAME_COLLISIONSYSTEM_H
