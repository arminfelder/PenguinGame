

#ifndef GAME_INPUTSYSTEM_H
#define GAME_INPUTSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems{
    class InputSystem: public System {
    public:
        InputSystem(Managers::EventsManager *pEventsManager);
        void update();

    private:
        Managers::EventsManager *mEventsManager = nullptr;
    };
}

#endif //GAME_INPUTSYSTEM_H
