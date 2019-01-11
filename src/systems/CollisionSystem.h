#ifndef GAME_COLLISIONSYSTEM_H
#define GAME_COLLISIONSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class CollisionSystem: public System {
    public:
        CollisionSystem(Managers::EventsManager *pEventsmanager);
        void changeCollisionMask(std::vector<bool> *collisionMask);
        void changeMapWidth(int width);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
        std::vector<bool> *collisionMask = nullptr;
        int mapWidth = -1;

    };
}


#endif //GAME_COLLISIONSYSTEM_H
