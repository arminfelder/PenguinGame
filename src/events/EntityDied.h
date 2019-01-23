//
// Created by armin on 22.01.19.
//

#ifndef GAME_ENTITYDIED_H
#define GAME_ENTITYDIED_H

#include "Event.h"

namespace Events {
    class EntityDied:public Event {
    public:
        EntityDied(int pEntity, int pOrigHealth);
        int mEntity;
        int mOrigHealth;
    };
}


#endif //GAME_ENTITYDIED_H
