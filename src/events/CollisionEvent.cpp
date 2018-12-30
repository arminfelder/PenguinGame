//
// Created by armin on 30.12.18.
//

#include "CollisionEvent.h"

Events::CollisionEvent::CollisionEvent(int pMovingEntity, int pCollidingEntity, Events::collisionTypes pType):Event(EventTypes::Collision),mType(pType),
mMovingEntity(pMovingEntity),mCollidingEntity(pCollidingEntity){

}
