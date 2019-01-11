

#include "KeyDownEvent.h"

Events::KeyDownEvent::KeyDownEvent(SDL_Keysym pCode):Event(EventTypes::KeyDown),mKeyCode(pCode) {

}
