//
// Created by armin on 14.02.19.
//

#ifndef GAME_OWNERSHIP_H
#define GAME_OWNERSHIP_H

#include "Component.h"
namespace Components {
    class Ownership: public Component {
    public:
        Ownership(int pId);
        int mId;
    };
}


#endif //GAME_OWNERSHIP_H
