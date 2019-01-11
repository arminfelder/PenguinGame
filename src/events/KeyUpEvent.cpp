

#include "KeyUpEvent.h"

Events::KeyUpEvent::KeyUpEvent(SDL_Keysym pCode):Event(EventTypes::KeyUp),mKeyCode(pCode) {

}
