//
// Created by armin on 10.01.19.
//

#ifndef GAME_PHYSICSSYSTEM_H
#define GAME_PHYSICSSYSTEM_H

#include <tiff.h>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class PhysicsSystem {
    public:
        PhysicsSystem(Managers::EventsManager *pEventsManager);
        void update(uint64);

    private:
        Managers::EventsManager *mEventsManager;
    };
}


#endif //GAME_PHYSICSSYSTEM_H
