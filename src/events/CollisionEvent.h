//
// Created by armin on 30.12.18.
//

#ifndef GAME_COLLISIONEVENT_H
#define GAME_COLLISIONEVENT_H

#include "Event.h"

namespace Events {
    enum class collisionTypes{
        regular,
        ladder
    };
    class CollisionEvent:public Event {

    public:
        CollisionEvent(int pMovingEntity, int pCollidingEntity, collisionTypes pType);
        collisionTypes mType;
        int mMovingEntity;
        int mCollidingEntity;
    };

}


#endif //GAME_COLLISIONEVENT_H
