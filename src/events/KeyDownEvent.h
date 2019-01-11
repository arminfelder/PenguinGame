

#ifndef GAME_KEYDOWNEVENT_H
#define GAME_KEYDOWNEVENT_H

#include <SDL_keycode.h>
#include <SDL_system.h>
#include "Event.h"

namespace Events {
    class KeyDownEvent:public Event {
    public:
        KeyDownEvent(SDL_Keysym pCode);
        SDL_Keysym mKeyCode;
    };

}


#endif //GAME_KEYDOWNEVENT_H
