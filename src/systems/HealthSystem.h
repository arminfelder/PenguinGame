//
// Created by armin on 22.12.18.
//

#ifndef GAME_HEALTHSYSTEM_H
#define GAME_HEALTHSYSTEM_H

#include <functional>
#include <memory>
#include "System.h"
#include "../managers/EventsManager.h"
#include "../events/HealthEvent.h"

namespace Systems {
    class HealthSystem {
    public:
        HealthSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager = nullptr;
    };
}


#endif //GAME_HEALTHSYSTEM_H
