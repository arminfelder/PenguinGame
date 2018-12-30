//
// Created by armin on 27.12.18.
//

#ifndef GAME_KEYUPEVENT_H
#define GAME_KEYUPEVENT_H

#include <SDL_keycode.h>
#include <SDL_system.h>
#include "Event.h"

namespace Events {
    class KeyUpEvent:public Event {
    public:
        KeyUpEvent(SDL_Keysym pCode);
        SDL_Keysym mKeyCode;
    };
}


#endif //GAME_KEYUPEVENT_H
