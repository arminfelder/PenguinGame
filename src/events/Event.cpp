#include "Event.h"

Events::Event::Event(Events::EventTypes pType):type(pType) {
}

Events::EventTypes Events::Event::getType() {
    return type;
}
