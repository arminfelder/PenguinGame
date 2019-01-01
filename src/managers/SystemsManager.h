//
// Created by armin on 20.12.18.
//

#ifndef GAME_SYSTEMSMANAGER_H
#define GAME_SYSTEMSMANAGER_H

#include "../systems/HealthSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/PositionSystem.h"
#include "../systems/InputSystem.h"
#include "../managers/EventsManager.h"
#include "../systems/CollisionSystem.h"

namespace Managers {

    class SystemsManager {
    public:

        SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer, EventsManager *pEventsManager);
        void sendEvent();

        void update(uint64_t pTimeDiff);

        Systems::HealthSystem *getMHealthSystem() const;

        Systems::RenderSystem *getMRenderSystem() const;

    private:
        Systems::RenderSystem* mRenderSystem = nullptr;
        Systems::HealthSystem* mHealthSystem = nullptr;
        Systems::PositionSystem* mPositionSystem = nullptr;
        Systems::InputSystem* mInputSystem = nullptr;
        Systems::CollisionSystem* mCollisionSystem = nullptr;

        Managers::EventsManager* mEventsManager = nullptr;

    };
}

#endif //GAME_SYSTEMSMANAGER_H
