//
// Created by armin on 27.12.18.
//

#include "KeyPressedEvent.h"

using namespace Events;
KeyPressedEvent::KeyPressedEvent(SDL_Keysym pCode):Event(EventTypes::Input) ,mKeyCode(pCode) {

}
