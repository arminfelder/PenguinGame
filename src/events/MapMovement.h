#ifndef GAME_MAPMOVEMENT_H
#define GAME_MAPMOVEMENT_H
#include "Event.h"

namespace Events {
    class MapMovement: public Event {
    public:
        enum class direction{
            right,
            left,
            up,
            down
        };
        MapMovement(direction direction);

    private:
        direction mMapMovement;
    };
}


#endif //GAME_MAPMOVEMENT_H
