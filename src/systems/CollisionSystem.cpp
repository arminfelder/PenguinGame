/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <iostream>
#include "CollisionSystem.h"
#include "../events/EntityMoved.h"
#include "../events/CollisionEvent.h"
#include "../managers/ComponentsManager.h"
#include "../managers/EntityManager.h"
#include "../MapParser.h"
#include "../events/FallingEvent.h"

Systems::CollisionSystem::CollisionSystem(Managers::EventsManager *pEventsmanager):mEventsManager(pEventsmanager) {

    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::EntityMoved*>(pEvent.get());
        auto entityId = event->mEntityId;
        auto movingEntity = Managers::EntityManager::getEntity(event->mEntityId);

        auto collideAbles = Managers::ComponentsManager::getCollideAble();

        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = Managers::ComponentsManager::getVisualComponent(entityId);

        int rightLimit = visual->mImageRect.w + spatial->mPositionX;
        int leftLimit = spatial->mPositionX;
        int topLimit = spatial->mPositionY;
        int bottomLimit = spatial->mPositionY + visual->mImageRect.h;

        //maskCollision

        bool maskCollision = false;
        int maskRightLimit = static_cast<int>(ceil(static_cast<double>(rightLimit)/50.0));
        int maskLeftLimit =  static_cast<int>(ceil(static_cast<double>(leftLimit)/50.0));
        int maskTopLimit =   static_cast<int>(ceil(static_cast<double>(topLimit)/50.0));
        int maskBottomLimit =static_cast<int>(ceil(static_cast<double>(bottomLimit)/50.0));

        for (int horizontal = maskLeftLimit-1; horizontal < maskRightLimit; horizontal++) {
            for (int vertical = maskTopLimit-1; vertical < maskBottomLimit; vertical++) {
                unsigned long index = static_cast<unsigned long>(horizontal + vertical * system->mapWidth);
                try {
                    if (system->collisionMask->size() > index && (system->collisionMask->at(index)) == true) {
                        std::cout << "collision via mask detected" << std::endl;
                        maskCollision = true;
                        system->mEventsManager->addEvent(
                                std::make_shared<Events::CollisionEvent>(entityId, 0, Events::collisionTypes::regular));
                    }
                }
                catch (const std::out_of_range& e) {//player dies -> game over //todo use our own event system
                    SDL_Event sdlEvent;
                    sdlEvent.type = 33332;
                    SDL_PushEvent(&sdlEvent);
                }
            }
        }

        //end maskCollision

        bool entityCollision = false;
        if (!maskCollision) {
            for (const auto &entry: collideAbles) {
                auto entrySpatial = Managers::ComponentsManager::getSpatialComponent(entry.first);
                auto entryVisual = Managers::ComponentsManager::getVisualComponent(entry.first);
                auto entryEntity = Managers::EntityManager::getEntity(entry.first);
                int entryRightLimit = entryVisual->mImageRect.w + entrySpatial->mPositionX;
                int entryLeftLimit = entrySpatial->mPositionX;
                int entryTopLimit = entrySpatial->mPositionY;
                int entryBottomLimit = entrySpatial->mPositionY + entryVisual->mImageRect.h;

                Events::collisionTypes collisionType;
                switch (entryEntity->getType()) {
                    case Entities::entityTypes::wall: {
                        collisionType = Events::collisionTypes::regular;
                        break;
                    }
                    case Entities::entityTypes::ladder: {
                        collisionType = Events::collisionTypes::ladder;
                        break;
                    }
                    case Entities::entityTypes::npc: {
                        collisionType = Events::collisionTypes::npc;

                        break;
                    }
                    case Entities::entityTypes::movementReset: {
                        collisionType = Events::collisionTypes::movementReset;
                        break;
                    }
                    case Entities::entityTypes::ladderEnd: {
                        collisionType = Events::collisionTypes::ladderEnd;
                        break;
                    }
                    case Entities::entityTypes::ladderBegin: {
                        collisionType = Events::collisionTypes::ladderBegin;
                        break;
                        //TODO: add break with its own commit
                    }
                    case Entities::entityTypes::healthUp: {
                        collisionType = Events::collisionTypes::healthUp;
                        break;
                    }
                    case Entities::entityTypes::projectile:{
                        collisionType = Events::collisionTypes::bullet;
                        break;
                    }
                    case Entities::entityTypes::player:{
                        collisionType = Events::collisionTypes::player;
                        break;
                    }
                    case Entities::entityTypes::door:{
                        collisionType = Events::collisionTypes::regular;
                        break;
                    }
                    case Entities::entityTypes::key:{
                        collisionType = Events::collisionTypes::keyArea2;
                        break;
                    }
                    case Entities::entityTypes::teleporterEntrance:{
                        collisionType = Events::collisionTypes::teleporterEntry;
                        break;
                    }
                    case Entities::entityTypes::none: {
                        break;
                    }

                }
                if (leftLimit > entryLeftLimit && leftLimit < entryRightLimit) {
                    if (topLimit > entryTopLimit && topLimit < entryBottomLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                        entityCollision = true;
                    } else if (bottomLimit < entryBottomLimit && bottomLimit > entryTopLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        entityCollision = true;
                        std::cout << "collision!" << std::endl;
                    }
                } else if (rightLimit < entryRightLimit && rightLimit > entryLeftLimit) {
                    if (topLimit > entryTopLimit && topLimit < entryBottomLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                        entityCollision = true;

                    } else if (bottomLimit < entryBottomLimit && bottomLimit > entryTopLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                        entityCollision = true;

                    }
                }
            }
        }

        if (!maskCollision && !entityCollision && movingEntity->getType() == Entities::entityTypes::player) {
            //gravitation
                int floorLeftPosition = (maskBottomLimit) * system->mapWidth + maskLeftLimit - 1;
                int floorRightPosition = (maskBottomLimit) * system->mapWidth + maskRightLimit - 1;
                if(floorLeftPosition <system->collisionMask->size() && floorRightPosition<system->collisionMask->size()) {
                    bool floorLeft = system->collisionMask->at(static_cast<unsigned long>(floorLeftPosition));
                    bool floorRight = system->collisionMask->at(static_cast<unsigned long>(floorRightPosition));
                    if (!floorLeft && !floorRight) { //no floor below us -> fall down
                        system->mEventsManager->addEvent(std::make_shared<Events::FallingEvent>(entityId));
                        std::cout << "added event for falling" << std::endl;
                    } else if (maskTopLimit ==
                               maskBottomLimit) { //else: player lands somewhere, if: stop if player occupies only one cube
                        //todo make this hack nice using the event queue
                        auto momenta = Managers::ComponentsManager::getMomenta();
                        momenta[entityId]->speedY = 0;
                    }
                }
            //end gravitation
        }

    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityMoved, callback);
}

void Systems::CollisionSystem::changeCollisionMask(std::vector<bool> *collisionMask) {
    this->collisionMask = collisionMask;
}

void Systems::CollisionSystem::changeMapWidth(int width) {
    mapWidth = width;
}
