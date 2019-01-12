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

#include <SDL_events.h>
#include "InputSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyUpEvent.h"

using namespace Systems;
void InputSystem::update() {
    SDL_Event event;

    while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_MOUSEWHEEL)){
        switch (event.type){

            case SDL_KEYDOWN: {
                mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(event.key.keysym));
                break;
            }
            case SDL_KEYUP: {
                mEventsManager->addEvent(std::make_shared<Events::KeyUpEvent>(event.key.keysym));
                break;
            }
        }
    }
}

InputSystem::InputSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
}
