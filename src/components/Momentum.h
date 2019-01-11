#ifndef GAME_MOMENTUM_H
#define GAME_MOMENTUM_H

#include "Component.h"

namespace Components {
    class Momentum: public Component {
    public:
        Momentum();
    public:
        double gravitation = 10;
        double speedX = 0;
        double speedY = 0;
    };
}


#endif //GAME_MOMENTUM_H
