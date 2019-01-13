//
// Created by armin on 13.01.19.
//

#ifndef GAME_COLLISIONDAMAGE_H
#define GAME_COLLISIONDAMAGE_H

#include "Component.h"

namespace Components {
    class CollisionDamage:public Component {
    public:
        CollisionDamage(int pDamage);
        int mDamage;
    };
}


#endif //GAME_COLLISIONDAMAGE_H
