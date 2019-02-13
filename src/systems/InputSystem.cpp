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
#include <iostream>
#include "InputSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyUpEvent.h"

using namespace Systems;
void InputSystem::update(Uint64 pTimeDiff) {
    SDL_Event event;


    while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_MOUSEWHEEL)){

        switch (event.type){

            case SDL_KEYDOWN: {
              //  mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(event.key.keysym,std::move(keyVec)));
                mPressedKeys.insert(event.key.keysym);
                break;
            }
            case SDL_KEYUP: {
              //  mEventsManager->addEvent(std::make_shared<Events::KeyUpEvent>(event.key.keysym,std::move(keyVec)));
                mPressedKeys.erase(event.key.keysym);
                break;
            }
        }
    }
    static Uint64 lastTimeDiff = 0;
    static Uint64 rate = 40;
    if(lastTimeDiff+pTimeDiff >= rate) {
        auto length = 0;
        auto keys = SDL_GetKeyboardState(&length);
        std::vector<Uint8> keyVec(length);
        std::copy(keys,keys+length,keyVec.begin());

        for (const auto key: mPressedKeys) {
            mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(key, keyVec));
            if(key.sym != SDLK_LEFT && key.sym != SDLK_RIGHT){
                mPressedKeys.erase(key);
            }
        }
        lastTimeDiff -= rate;
    }
    lastTimeDiff += pTimeDiff;
}

InputSystem::InputSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {

}
