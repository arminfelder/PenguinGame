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

#include <unordered_set>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems{
    struct KeySymHash {
    public:
        size_t operator()(const SDL_Keysym & sym) const {
            return std::hash<int>()(sym.sym);
        }
    };
    struct KeySymEqual {
    public:
        bool operator()(const SDL_Keysym & sym1, const SDL_Keysym & sym2) const {

            if ( sym1.sym == sym2.sym )
                return true;
            else
                return false;
        }
    };
    class InputSystem: public System {
    public:
        InputSystem(Managers::EventsManager *pEventsManager);
        void update(Uint64 pTimeDiff);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        std::unordered_set<SDL_Keysym,KeySymHash, KeySymEqual> mPressedKeys;
        
    };
}

#endif //GAME_INPUTSYSTEM_H
