//
// Created by armin on 21.01.19.
//

#ifndef GAME_XP_H
#define GAME_XP_H

#include <zconf.h>
#include "Component.h"

namespace Components {
    class Xp:public Component {
    public:
        Xp();
        uint mXp;
    };
}


#endif //GAME_XP_H
