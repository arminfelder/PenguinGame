//
// Created by armin on 17.01.19.
//

#ifndef GAME_TRIGGERACTIVATED_H
#define GAME_TRIGGERACTIVATED_H

#include "Event.h"

namespace Events {
    class TriggerActivated:public Event {
    public:
        TriggerActivated(int pTriggerId, int pEntityId);
        int mTriggeredEntity;
        int mActivatingEntity;
    };
}

#endif //GAME_TRIGGERACTIVATED_H
