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

#ifndef GAME_INPUTSYSTEM_H
#define GAME_INPUTSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems{
    class InputSystem: public System {
    public:
        InputSystem(Managers::EventsManager *pEventsManager);
        void update();

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        std::vector<SDL_Keysym> getPressedKeys(Uint8 pKeyMap);
    };
}

#endif //GAME_INPUTSYSTEM_H
