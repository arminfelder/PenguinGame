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


#ifndef GAME_HEALTHSYSTEM_H
#define GAME_HEALTHSYSTEM_H

#include <functional>
#include <memory>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "System.h"
#include "../managers/EventsManager.h"
#include "../events/HealthEvent.h"

namespace Systems {
    class HealthSystem {
    public:
        HealthSystem(SDL_Renderer *pRenderer, Managers::EventsManager *pEventsManager);
        void update(Uint64 pTimeDiff);
    private:
        Managers::EventsManager *mEventsManager = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        std::shared_ptr<TTF_Font> Sans;

    };
}


#endif //GAME_HEALTHSYSTEM_H
