//
// Created by armin on 14.02.19.
//

#ifndef GAME_CANOPEN_H
#define GAME_CANOPEN_H

#include "Component.h"

namespace Components {
    class CanOpen: public Component {

    public:
        enum class Areas{
            area1,
            area2,
            area3
        };
        CanOpen(const Areas &pArea);
        Areas mOpens;

    };
}


#endif //GAME_CANOPEN_H
