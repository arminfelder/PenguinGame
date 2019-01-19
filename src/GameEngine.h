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

#ifndef GAME_GAMEENGINE_H
#define GAME_GAMEENGINE_H

#include "managers/EntityManager.h"
#include "managers/ComponentsManager.h"
#include "managers/SystemsManager.h"
#include "managers/EventsManager.h"

class GameEngine {
public:
    GameEngine(SDL_Window *pWindow, SDL_Renderer *pPrenderer);
    void update(uint64_t timediff);

    Managers::EntityManager* getEntityManager();
    Managers::SystemsManager* getSystemsManager();
    Managers::EventsManager* getEventManager();
    ~GameEngine();

private:
    Managers::EntityManager* mEntityManager = nullptr;
    Managers::ComponentsManager* mComponentsManager = nullptr;
    Managers::SystemsManager* mSystemsManager = nullptr;
    Managers::EventsManager* mEventsManager = nullptr;
};


#endif //GAME_GAMEENGINE_H
