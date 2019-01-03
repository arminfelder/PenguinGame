#include "FallingEvent.h"

using namespace Events;
Events::FallingEvent::FallingEvent(int pEntityId):Event(EventTypes::Falling), mEntityId(pEntityId) {}
