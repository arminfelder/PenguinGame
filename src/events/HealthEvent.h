//
// Created by armin on 29.12.18.
//

#ifndef GAME_HEALTHEVENT_H
#define GAME_HEALTHEVENT_H

#include "Event.h"

namespace Events {
    class HealthEvent:public Event {
    public:
        HealthEvent(int pEntityId, int pDiff);
        int healthDiff;
        int entityId;
    };
}


#endif //GAME_HEALTHEVENT_H
