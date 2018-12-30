//
// Created by armin on 23.12.18.
//

#include "GameEngine.h"

using namespace Managers;
void GameEngine::update(int timediff) {
    mSystemsManager->update(timediff);
    mEventsManager->dispatch();
}

GameEngine::GameEngine(SDL_Window *pWindow, SDL_Renderer *pPrenderer) {
    mEventsManager = new EventsManager();
    mEntityManager = new EntityManager;
    mComponentsManager = new ComponentsManager;
    mSystemsManager = new SystemsManager(pWindow, pPrenderer, mEventsManager);
}

Managers::EntityManager *GameEngine::getEntityManager() {
    return mEntityManager;
}
