//
// Created by armin on 13.01.19.
//

#ifndef GAME_AISYSTEM_H
#define GAME_AISYSTEM_H

#include "../managers/EventsManager.h"
#include "System.h"

namespace Systems {
    class AiSystem:public System {
    public:
        AiSystem(Managers::EventsManager *pEventsManager);
        void update(uint8_t pTimeDiff);
    private:
        Managers::EventsManager *mEventsManager;
    };
}


#endif //GAME_AISYSTEM_H
