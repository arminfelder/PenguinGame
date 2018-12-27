//
// Created by armin on 20.12.18.
//

#ifndef GAME_SYSTEMSMANAGER_H
#define GAME_SYSTEMSMANAGER_H

#include "../systems/HealthSystem.h"
#include "../systems/RenderSystem.h"

namespace Managers {

    class SystemsManager {
    public:

        SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer);
        void sendEvent();

        void update(float pTimeDiff);

        Systems::HealthSystem *getMHealthSystem() const;

        Systems::RenderSystem *getMRenderSystem() const;

    private:
        Systems::RenderSystem* mRenderSystem = nullptr;
        Systems::HealthSystem* mHealthSystem = nullptr;


    };
}

#endif //GAME_SYSTEMSMANAGER_H
