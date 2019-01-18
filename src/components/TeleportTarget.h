//
// Created by armin on 17.01.19.
//

#ifndef GAME_TELEPORTTARGET_H
#define GAME_TELEPORTTARGET_H

#include "Component.h"

namespace Components {
    class TeleportTarget : public Component {
    public:
        TeleportTarget(int pTargetEntity);
        int mTargetEntity;
    };
}


#endif //GAME_TELEPORTTARGET_H
