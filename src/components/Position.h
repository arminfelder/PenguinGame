//
// Created by armin on 07.12.18.
//

#ifndef GAME_POSITION_H
#define GAME_POSITION_H


#include "Component.h"
namespace Components {

    class Position : Component {

    public:
        Position(int xPosition, int yPosition);

        void setPosition(int xPosition, int yPosition);

        int getXPosition();

        int getYPosition();

    private:
        int mX;
        int mY;
    };

}
#endif //GAME_POSITION_H
