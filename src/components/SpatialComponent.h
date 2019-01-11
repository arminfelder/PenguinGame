

#ifndef GAME_SPATIALCOMPONENT_H
#define GAME_SPATIALCOMPONENT_H

namespace Components {
    class SpatialComponent {
    public:
        SpatialComponent(int pPositionX, int pPositionY,bool pMoveWithMap = true);
        int mPositionX;
        int mPositionY;

        int mPrevPositionX = 0;
        int mPrevPositionY = 0;

        bool moveWithMap = true;

    };
}


#endif //GAME_SPATIALCOMPONENT_H
