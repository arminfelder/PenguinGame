

#include "KeyPressedEvent.h"

using namespace Events;
KeyPressedEvent::KeyPressedEvent(SDL_Keysym pCode):Event(EventTypes::KePressed) ,mKeyCode(pCode) {

}
