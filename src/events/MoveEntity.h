//
// Created by armin on 10.01.19.
//

#ifndef GAME_MOVEENTITY_H
#define GAME_MOVEENTITY_H

#include "Event.h"

namespace Events {
    class MoveEntity:public Event {
    public:
        MoveEntity(int pEntityId ,int pX, int pY);

        int mEntityId;
        int mX;
        int mY;
    };
}


#endif //GAME_MOVEENTITY_H
