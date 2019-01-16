//
// Created by armin on 14.01.19.
//

#ifndef GAME_ENTITYCANSEE_H
#define GAME_ENTITYCANSEE_H

#include "Event.h"

namespace Events {
    class EntityCanSee: public Event {
    public:
        EntityCanSee(int pSeeingEntity, int pSeenEntity);
        int mSeeingEntity;
        int mSeenEntity;
    };
}


#endif //GAME_ENTITYCANSEE_H
