//
// Created by armin on 17.01.19.
//

#include "TriggerActivated.h"

using namespace Events;
TriggerActivated::TriggerActivated(int pTriggerId, int pEntityId):Event(EventTypes::TriggerActivated),mTriggeredEntity(pTriggerId),mActivatingEntity(pEntityId) {

}
