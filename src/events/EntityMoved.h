//
// Created by armin on 29.12.18.
//

#ifndef GAME_ENTITYMOVED_H
#define GAME_ENTITYMOVED_H

#include "Event.h"

namespace Events {
    class EntityMoved: public Event {
    public:
        enum class Direction{
            up,
            down,
            left,
            right
        };
        EntityMoved(int pEntityId, Direction pDirection);
        const Events::EventTypes type = EventTypes::EntityMoved;

        int mEntityId;
        Direction mDirection;
    };
}


#endif //GAME_ENTITYMOVED_H
