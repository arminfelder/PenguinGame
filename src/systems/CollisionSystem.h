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

    private:
        Managers::EventsManager *mEventsManager = nullptr;
    };
}


#endif //GAME_COLLISIONSYSTEM_H
