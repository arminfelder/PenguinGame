//
// Created by armin on 25.01.19.
//

#ifndef GAME_EVADE_H
#define GAME_EVADE_H

#include "Component.h"

namespace Components {
    class EvadeCapability:public Component {
    public:
        EvadeCapability(int pEvadeProbability = 0);
        int mChance = 0;
    };
}


#endif //GAME_EVADE_H
