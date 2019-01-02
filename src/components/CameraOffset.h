#ifndef GAME_CAMERAOFFSET_H
#define GAME_CAMERAOFFSET_H

#include "Component.h"

namespace Components {
    class CameraOffset: public Component {
    public:
        CameraOffset(int pXOffset, int pYOffset);

        int xOffset = 0;
        int getXOffset() const;

        void setXOffset(int xOffset);

        int getYOffset() const;

        void setYOffset(int yOffset);

        int yOffset = 0;
    };
}


#endif //GAME_CAMERAOFFSET_H
