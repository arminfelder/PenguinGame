//
// Created by armin on 29.12.18.
//

#ifndef GAME_ENTITYMOVED_H
#define GAME_ENTITYMOVED_H

#include "Event.h"

namespace Events {
    class EntityMoved: public Event {
    public:
        EntityMoved(int pEntityId);
        const Events::EventTypes type = EventTypes::EntityMoved;

        int mEntityId;
    };
}


#endif //GAME_ENTITYMOVED_H
