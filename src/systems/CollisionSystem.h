//
// Created by armin on 30.12.18.
//

#ifndef GAME_COLLISIONSYSTEM_H
#define GAME_COLLISIONSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class CollisionSystem: public System {
    public:
        CollisionSystem(Managers::EventsManager *pEventsmanager);
        void changeCollisionMask(std::vector<bool> *collisionMask);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        std::vector<bool> *collisionMask = nullptr;

    };
}


#endif //GAME_COLLISIONSYSTEM_H
