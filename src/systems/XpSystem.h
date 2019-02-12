//
// Created by armin on 21.01.19.
//

#ifndef GAME_XPSYSTEM_H
#define GAME_XPSYSTEM_H

#include <SDL_system.h>
#include <SDL_ttf.h>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class XpSystem : public System {
    public:
        XpSystem(SDL_Renderer *pRenderer,Managers::EventsManager *pEventsManager);
        void drawXp(int pXp=-1);
    private:
        Managers::EventsManager *mEventsManager = nullptr;
        SDL_Renderer *mRenderer = nullptr;
        std::shared_ptr<TTF_Font> Sans;

    };
}


#endif //GAME_XPSYSTEM_H
