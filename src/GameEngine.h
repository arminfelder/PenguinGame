//
// Created by armin on 23.12.18.
//

#ifndef GAME_GAMEENGINE_H
#define GAME_GAMEENGINE_H

#include "managers/EntityManager.h"
#include "managers/ComponentsManager.h"
#include "managers/SystemsManager.h"
#include "managers/EventsManager.h"

class GameEngine {
public:
    GameEngine(SDL_Window *pWindow, SDL_Renderer *pPrenderer);
    void update(int timediff);

    Managers::EntityManager* getEntityManager();

private:
    Managers::EntityManager* mEntityManager = nullptr;
    Managers::ComponentsManager* mComponentsManager = nullptr;
    Managers::SystemsManager* mSystemsManager = nullptr;
    Managers::EventsManager* mEventsManager = nullptr;
};


#endif //GAME_GAMEENGINE_H
