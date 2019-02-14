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


#ifndef GAME_AUDIOSYSTEM_H
#define GAME_AUDIOSYSTEM_H

#include <SDL_audio.h>
#include <SDL_mixer.h>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class AudioSystem {
    public:
        AudioSystem(Managers::EventsManager *pEventsManager,const std::string &pArea ="area1");

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        SDL_AudioDeviceID mDeviceId;
        std::shared_ptr<Mix_Music> mArea1Music;
        std::shared_ptr<Mix_Music> mArea2Music;
        std::shared_ptr<Mix_Music> mArea3Music;
        std::shared_ptr<Mix_Chunk> mCollectItem;

    };
}


#endif //GAME_AUDIOSYSTEM_H
