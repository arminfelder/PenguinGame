//
// Created by armin on 27.12.18.
//

#ifndef GAME_KEYPRESSEDEVENT_H
#define GAME_KEYPRESSEDEVENT_H

#include <SDL_keycode.h>
#include <SDL_system.h>
#include "Event.h"

namespace Events {
    class KeyPressedEvent:public Event {
    public:
        KeyPressedEvent(SDL_Keysym pCode);
        SDL_Keysym mKeyCode;
    };
}


#endif //GAME_KEYPRESSEDEVENT_H
