#include "MapMovement.h"
using namespace Events;

MapMovement::MapMovement(Events::MapMovement::direction direction):
    Event(Events::EventTypes::MapMovement), mMapMovement{direction}
{

}
