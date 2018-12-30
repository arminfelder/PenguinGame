//
// Created by armin on 27.12.18.
//

#include "KeyDownEvent.h"

Events::KeyDownEvent::KeyDownEvent(SDL_Keysym pCode):Event(EventTypes::Input),mKeyCode(pCode) {

}
