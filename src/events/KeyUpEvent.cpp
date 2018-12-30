//
// Created by armin on 27.12.18.
//

#include "KeyUpEvent.h"

Events::KeyUpEvent::KeyUpEvent(SDL_Keysym pCode):Event(EventTypes::Input),mKeyCode(pCode) {

}
