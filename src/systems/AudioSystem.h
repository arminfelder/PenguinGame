//
// Created by armin on 03.01.19.
//

#ifndef GAME_AUDIOSYSTEM_H
#define GAME_AUDIOSYSTEM_H

#include <SDL_audio.h>
#include <SDL_mixer.h>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class AudioSystem {
    public:
        AudioSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        SDL_AudioDeviceID mDeviceId;
        std::shared_ptr<Mix_Music> mArea1Music;
        std::shared_ptr<Mix_Chunk> mTestSound;

    };
}


#endif //GAME_AUDIOSYSTEM_H
