#ifndef GAME_FALLINGEVENT_H
#define GAME_FALLINGEVENT_H
#include "Event.h"

namespace Events {
    class FallingEvent: public Event {
    public:
        FallingEvent(int pEntityId);

        int mEntityId;
    };
}


#endif //GAME_FALLINGEVENT_H
