//
// Created by armin on 29.12.18.
//

#include "HealthEvent.h"

Events::HealthEvent::HealthEvent(int pEntityId, int pDiff):Event( EventTypes::Health),healthDiff(pDiff),entityId(pEntityId) {

}
