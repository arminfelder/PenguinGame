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


#include <memory>
#include <SDL_mixer.h>
#include <iostream>
#include "AudioSystem.h"
#include "../events/Event.h"
#include "../managers/EventsManager.h"

Systems::AudioSystem::AudioSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto callback = [system = this] (const std::shared_ptr<Events::Event> &pEvent){
        switch (pEvent->getType()){
            case Events::EventTypes::Health:{

            }
        }
    };
    mArea1Music = std::shared_ptr<Mix_Music>(Mix_LoadMUS( "./res/04 All of Us.wav" ),Mix_FreeMusic);
    mTestSound = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV("./res/163442__under7dude__man-dying.wav"),Mix_FreeChunk);
    Mix_PlayMusic( mArea1Music.get(), -1 );
}
