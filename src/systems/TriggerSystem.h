//
// Created by armin on 12.01.19.
//

#ifndef GAME_TRIGGERSYSTEM_H
#define GAME_TRIGGERSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"
#include "../components/UseAble.h"

namespace Systems {
    class TriggerSystem: public System {
    public:
        TriggerSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager;
        static bool collidesBottomTop(int playerBottomLimit, int playerTopLimit, int entryBottomLimit, int entryTopLimit);
    };
}


#endif //GAME_TRIGGERSYSTEM_H
