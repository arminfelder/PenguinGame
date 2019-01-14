//
// Created by armin on 14.01.19.
//

#include "EntityCanSee.h"

using namespace Events;
EntityCanSee::EntityCanSee(int pSeeingEntity, int pSeenEntity):Event(EventTypes::EntityCanSee),mSeeingEntity(pSeeingEntity),mSeenEntity(pSeenEntity) {

}
