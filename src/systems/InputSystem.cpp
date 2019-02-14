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



    static Uint64 lastTimeDiff = 0;
    const Uint64 rate = 15;
    lastTimeDiff += pTimeDiff;
    if(lastTimeDiff >= rate) {
        while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_MOUSEWHEEL)){

            switch (event.type){

                case SDL_KEYDOWN: {
                    //  mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(event.key.keysym,std::move(keyVec)));
                    if (event.key.keysym.scancode != SDL_SCANCODE_UNKNOWN) {
                        mPressedKeys.emplace(event.key.keysym);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    //  mEventsManager->addEvent(std::make_shared<Events::KeyUpEvent>(event.key.keysym,std::move(keyVec)));
                    if(mPressedKeys.find(event.key.keysym) != mPressedKeys.end()) {
                        mPressedKeys.erase(event.key.keysym);
                    }
                    break;
                }
            }
        }
        auto length = 0;
        auto keys = SDL_GetKeyboardState(&length);
        std::vector<Uint8> keyVec(length);
        std::copy(keys,keys+length,keyVec.begin());

        if(!mPressedKeys.empty()) {
                for (const auto &elem: mPressedKeys) {
                    if (elem.scancode != SDL_SCANCODE_UNKNOWN) {
                        mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(elem, keyVec));
                        if (elem.sym != SDLK_LEFT && elem.sym != SDLK_RIGHT) {
                            mPressedKeys.erase(elem);
                        }
                    }
                }
            }


        lastTimeDiff = 0;
    }
}

InputSystem::InputSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {

}
