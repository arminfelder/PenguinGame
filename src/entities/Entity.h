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

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include <SDL_render.h>
#include <vector>
#include "../components/Component.h"
namespace Entities {
    enum class entityTypes{
        player,
        npc,
        wall,
        ladder,
        movementReset,
        ladderEnd,
        ladderBegin,
        healthIndicator,
        healthUp,
        projectile,
        key,
        door,
        teleporterEntrance,
        teleporterTarget,
        xpIndicator,
        savePoint,
        disc,
        ak47,
        shield,
        none,
        mapChanger,
        doubleJumpEnabler
    };
    class Entity {
    public:
        Entity(int id, entityTypes pType = entityTypes::none);

        int getId() const;
        entityTypes getType();

    protected:
        int mId;
        entityTypes mEntityType;
    };
}

#endif //GAME_ENTITY_H
