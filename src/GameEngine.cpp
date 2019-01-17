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

#include "GameEngine.h"

using namespace Managers;
void GameEngine::update(uint64_t timediff) {
    mSystemsManager->update(timediff);
    mEventsManager->dispatch(timediff);
}

GameEngine::GameEngine(SDL_Window *pWindow, SDL_Renderer *pPrenderer) {
    mEventsManager = new EventsManager();
    mEntityManager = new EntityManager;
    mComponentsManager = new ComponentsManager;
    mSystemsManager = new SystemsManager(pWindow, pPrenderer, mEventsManager);
}

Managers::EntityManager *GameEngine::getEntityManager() {
    return mEntityManager;
}

Managers::SystemsManager *GameEngine::getSystemsManager() {
    return mSystemsManager;
}

GameEngine::~GameEngine() {
    mEventsManager->~EventsManager();
    mEventsManager = nullptr;
    mEntityManager->~EntityManager();
    mEntityManager = nullptr;
    mComponentsManager->~ComponentsManager();
    mComponentsManager = nullptr;
    mSystemsManager->~SystemsManager();
    mSystemsManager = nullptr;
}
