//
// Created by armin on 22.12.18.
//

#ifndef GAME_HEALTHSYSTEM_H
#define GAME_HEALTHSYSTEM_H

#include <functional>
#include <memory>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "System.h"
#include "../managers/EventsManager.h"
#include "../events/HealthEvent.h"

namespace Systems {
    class HealthSystem {
    public:
        HealthSystem(SDL_Renderer *pRenderer, Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        std::shared_ptr<TTF_Font> Sans;

    };
}


#endif //GAME_HEALTHSYSTEM_H
