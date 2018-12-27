//
// Created by armin on 27.12.18.
//

#ifndef GAME_SPATIALCOMPONENT_H
#define GAME_SPATIALCOMPONENT_H

namespace Components {
    class SpatialComponent {
    public:
        SpatialComponent(int pPositionX, int pPositionY);
        int mPositionX;
        int mPositionY;

    };
}


#endif //GAME_SPATIALCOMPONENT_H
