//
// Created by armin on 03.01.19.
//

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
