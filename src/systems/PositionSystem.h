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


#ifndef GAME_POSITIONSYSTEM_H
#define GAME_POSITIONSYSTEM_H

#include "../managers/EventsManager.h"
#include "../events/KeyUpEvent.h"
#include "System.h"

namespace Systems {
    class PositionSystem : public System {
    public:
        PositionSystem(Managers::EventsManager *pEventsManager);
        void update();

    private:
        Managers::EventsManager *mEventsManager = nullptr;
    };
}


#endif //GAME_POSITIONSYSTEM_H
