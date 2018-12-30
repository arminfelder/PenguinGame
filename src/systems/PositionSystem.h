//
// Created by armin on 29.12.18.
//

#ifndef GAME_POSITIONSYSTEM_H
#define GAME_POSITIONSYSTEM_H

#include "../managers/EventsManager.h"
#include "../events/KeyUpEvent.h"
#include "System.h"

namespace Systems {
    class PositionSystem : public System {
    public:
        PositionSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
    };
}


#endif //GAME_POSITIONSYSTEM_H
