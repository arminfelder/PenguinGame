//
// Created by armin on 12.01.19.
//

#ifndef GAME_TRIGGERSYSTEM_H
#define GAME_TRIGGERSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class TriggerSystem: public System {
    public:
        TriggerSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager;
    };
}


#endif //GAME_TRIGGERSYSTEM_H
