#ifndef GAME_COLLIDEABLE_H
#define GAME_COLLIDEABLE_H

#include "Component.h"

namespace Components {

    class CollideAble:Component {
    public:
        bool active = true;
    };
}


#endif //GAME_COLLIDEABLE_H
