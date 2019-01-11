#ifndef GAME_MOVEABLECOMPONENT_H
#define GAME_MOVEABLECOMPONENT_H

#include "Component.h"

namespace Components {
    class MoveAbleComponent:public Component {
    public:
        MoveAbleComponent();
        MoveAbleComponent(bool pRight, bool pDown, bool pLeft, bool pTop);
        bool canMoveLeft = false;
        bool canMoveRight = false;
        bool canMoveDown = false;
        bool canMoveUp = false;

    };
}


#endif //GAME_MOVEABLECOMPONENT_H
