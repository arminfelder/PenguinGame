//
// Created by armin on 25.01.19.
//

#ifndef GAME_EVADE_H
#define GAME_EVADE_H

#include <string>
#include <vector>
#include "Component.h"

namespace Components {
    class EvadeCapability:public Component {
    public:
        EvadeCapability(int pEvadeProbability = 0);
        std::string serialize();
        bool load(std::vector<std::string> splittedStrings);
        int mChance = 0;
    };
}


#endif //GAME_EVADE_H
