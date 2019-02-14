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

Systems::AudioSystem::AudioSystem(Managers::EventsManager *pEventsManager,const std::string &pArea):mEventsManager(pEventsManager) {
    auto callback = [system = this] (const std::shared_ptr<Events::Event> &pEvent){
        switch (pEvent->getType()){
            case Events::EventTypes::Health:{
                Mix_VolumeChunk(system->mCollectItem.get(), MIX_MAX_VOLUME);
                Mix_PlayChannel( -1, system->mCollectItem.get(), 0 );
                break;
            }
            default:{

            }
        }
    };
    mArea1Music = std::shared_ptr<Mix_Music>(Mix_LoadMUS( "./res/04 All of Us.wav" ),Mix_FreeMusic);
    mArea2Music = std::shared_ptr<Mix_Music>(Mix_LoadMUS("./res/Intro Theme.mp3"),Mix_FreeMusic);
    mArea3Music = std::shared_ptr<Mix_Music>(Mix_LoadMUS("./res/Desert Theme.mp3"),Mix_FreeMusic);

    mCollectItem = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV("./res/387133__rdaly95__collecting-health.wav"),Mix_FreeChunk);

    if(pArea == "area1" ){
        Mix_PlayMusic( mArea1Music.get(), -1 );
    }else if(pArea == "area2"){
        Mix_PlayMusic( mArea2Music.get(), -1 );
    }else if(pArea == "area3"){
        Mix_PlayMusic( mArea3Music.get(), -1 );
    }

    Mix_VolumeMusic(50);
    mEventsManager->regsiterEventHandler(Events::EventTypes::Health, callback);
}
