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

#ifndef GAME_COLLISIONEVENT_H
#define GAME_COLLISIONEVENT_H

#include "Event.h"

namespace Events {
    enum class collisionTypes{
        regular,
        ladder,
        ladderEnd,
        ladderBegin,
        movementReset,
        healthUp,
        bullet,
        npc,
        player,
        keyArea2,
        teleporterEntry,
        disc,
        savePoint,
        ak47,
        shield
    };
    class CollisionEvent:public Event {

    public:
        CollisionEvent(int pMovingEntity, int pCollidingEntity, collisionTypes pType);
        collisionTypes mType;
        int mMovingEntity;
        int mCollidingEntity;
    };

}


#endif //GAME_COLLISIONEVENT_H
