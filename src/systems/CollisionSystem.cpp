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
#include "../events/MoveEntity.h"

Systems::CollisionSystem::CollisionSystem(Managers::EventsManager *pEventsmanager) : mEventsManager(pEventsmanager) {

    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent) -> void {
        auto event = static_cast<Events::EntityMoved *>(pEvent.get());
        auto entityId = event->mEntityId;
        auto movingEntity = Managers::EntityManager::getEntity(event->mEntityId);
        if (movingEntity ==
            nullptr) //map was redrawn, therefore, there might still be a move event (most probably by enemies) which are no longer present
            return;

        auto collideAbles = Managers::ComponentsManager::getCollideAble();

        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = Managers::ComponentsManager::getVisualComponent(entityId);

        int rightLimit = visual->mImageRect.w + spatial->mPositionX;
        int leftLimit = spatial->mPositionX;
        int topLimit = spatial->mPositionY;
        int bottomLimit = spatial->mPositionY + visual->mImageRect.h;

        //maskCollision

        bool maskCollision = false;
        int maskRightLimit = static_cast<int>(ceil(static_cast<double>(rightLimit) / 50.0));
        int maskLeftLimit = static_cast<int>(ceil(static_cast<double>(leftLimit) / 50.0));
        int maskTopLimit = static_cast<int>(ceil(static_cast<double>(topLimit) / 50.0));
        int maskBottomLimit = static_cast<int>(ceil(static_cast<double>(bottomLimit) / 50.0));

        for (int horizontal = maskLeftLimit - 1; horizontal < maskRightLimit; horizontal++) {
            for (int vertical = maskTopLimit - 1; vertical < maskBottomLimit; vertical++) {
                int index = (horizontal + vertical * system->mapWidth);
                try {
                    if (system->collisionMask->size() > static_cast<unsigned long>(index) &&
                        (system->collisionMask->at(static_cast<unsigned long>(index))) == true) {
                        std::cout << "collision via mask detected" << std::endl;
                        maskCollision = true;
                        bool collisionTop = system->collisionMask->at(
                                horizontal + system->mapWidth * (maskTopLimit - 1));
                        bool collisionBottom = system->collisionMask->at(
                                horizontal + system->mapWidth * (maskBottomLimit - 1));
                        if (movingEntity.get()->getType() ==
                            Entities::entityTypes::projectile) //if projectile collides with wall, remove it
                            Managers::EntityManager::destroyEntity(entityId);
                        if (entityId == 1 && !collisionTop && collisionBottom) { //set player at position of upper space
                            spatial->mPositionY = (maskTopLimit - 1) * 50;
                            system->mEventsManager->addEvent(
                                    std::make_shared<Events::MoveEntity>(1, 0, 1)); //move player to correct position
                            return;
                        } else if (entityId == 1 && collisionTop &&
                                   !collisionBottom) { //collision while jumping, set back
                            spatial->mPositionY = (maskBottomLimit - 1) * 50;
                            spatial->mPrevPositionY = spatial->mPositionY + 1;
                            system->mEventsManager->addEvent(
                                    std::make_shared<Events::MoveEntity>(1, 0, 1)); //move player to correct position

                            return;
                        } else
                            system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, 0,
                                                                                                      Events::collisionTypes::regular));

                    } else if (entityId == 1 && index >= static_cast<int>(system->collisionMask->size())) {//player dies -> game over //todo use our own event system
                        SDL_Event sdlEvent;
                        sdlEvent.type = 33332;
                        SDL_PushEvent(&sdlEvent);
                    }
                }
                catch (const std::exception &) {//player dies -> game over //todo use our own event system
                    if (entityId == 1) {
                        SDL_Event sdlEvent;
                        sdlEvent.type = 33332;
                        SDL_PushEvent(&sdlEvent);
                    }
                }

            }
        }

        //end maskCollision

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
                    }
                    case Entities::entityTypes::healthUp: {
                        collisionType = Events::collisionTypes::healthUp;
                        break;
                    }
                    case Entities::entityTypes::projectile: {
                        collisionType = Events::collisionTypes::bullet;
                        break;
                    }
                    case Entities::entityTypes::player: {
                        collisionType = Events::collisionTypes::player;
                        break;
                    }
                    case Entities::entityTypes::door: {
                        collisionType = Events::collisionTypes::regular;
                        break;
                    }
                    case Entities::entityTypes::key: {
                        collisionType = Events::collisionTypes::keyArea2;
                        break;
                    }
                    case Entities::entityTypes::teleporterEntrance: {
                        collisionType = Events::collisionTypes::teleporterEntry;
                        break;
                    }
                    case Entities::entityTypes::disc: {
                        collisionType = Events::collisionTypes::disc;
                        break;
                    }
                    case Entities::entityTypes::savePoint: {
                        collisionType = Events::collisionTypes::savePoint;
                        break;
                    }
                    case Entities::entityTypes::ak47: {
                        collisionType = Events::collisionTypes::ak47;
                        break;
                    }
                    case Entities::entityTypes::shield: {
                        collisionType = Events::collisionTypes::shield;
                        break;
                    }
                    case Entities::entityTypes::mapChanger: {
                        collisionType = Events::collisionTypes::mapChanger;
                        break;
                    }
                    default:
                    case Entities::entityTypes::none: {
                        break;
                    }
                    case Entities::entityTypes::healthIndicator:break;
                    case Entities::entityTypes::teleporterTarget:break;
                    case Entities::entityTypes::xpIndicator:break;
                }
                if (leftLimit > entryLeftLimit && leftLimit < entryRightLimit)
                    system->detectCollision(topLimit, entryTopLimit, bottomLimit, entryBottomLimit, entityId, collisionType, entry, system->mEventsManager);
                else if (rightLimit < entryRightLimit && rightLimit > entryLeftLimit)
                    system->detectCollision(topLimit, entryTopLimit, bottomLimit, entryBottomLimit, entityId, collisionType, entry, system->mEventsManager);


            }
        }

        if (!maskCollision && movingEntity->getType() == Entities::entityTypes::player) { //also fall down if entity collision happened
            //gravitation
            auto floorLeftPosition = static_cast<unsigned long>((maskBottomLimit) * system->mapWidth + maskLeftLimit - 1);
            auto floorRightPosition = static_cast<unsigned long>((maskBottomLimit) * system->mapWidth + maskRightLimit - 1);
            if (floorLeftPosition < system->collisionMask->size() &&
                floorRightPosition < system->collisionMask->size()) {
                bool floorLeft = system->collisionMask->at(floorLeftPosition);
                bool floorRight = system->collisionMask->at(floorRightPosition);
                if (!floorLeft && !floorRight) { //no floor below us -> fall down
                    if (!Managers::ComponentsManager::getMoveableComponent(1).get()->climbing) { //only fall, if the player is not climbing at the moment
                        system->mEventsManager->addEvent(std::make_shared<Events::FallingEvent>(entityId));
                        std::cout << "added event for falling" << std::endl;
                    }
                } else if (maskTopLimit == maskBottomLimit) { //else: player lands somewhere, if: stop if player occupies only one cube
                    //todo make this hack nice using the event queue
                    auto momenta = Managers::ComponentsManager::getMomenta();
                    momenta[entityId]->speedY = 0;
                    momenta[entityId]->speedX = 0;
                    auto moveAbleComponent = Managers::ComponentsManager::getMoveableComponent(1);
                    moveAbleComponent->doubleJumpUsed = false;
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

bool Systems::CollisionSystem::detectCollision(int topLimit, int entryTopLimit, int bottomLimit, int entryBottomLimit, int entityId, Events::collisionTypes collisionType,
                                               const std::pair<int, std::shared_ptr<Components::CollideAble>> &entry, Managers::EventsManager* mEventsManager) {
    bool entityCollision = false;

    if (collisionType == Events::collisionTypes::ladder) {
        if ((topLimit > entryTopLimit && topLimit < entryBottomLimit) || (bottomLimit < entryBottomLimit && bottomLimit > entryTopLimit)) {
            std::cout << "collision!" << std::endl;
            entityCollision = true;
            mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
        }
    }
    else if (collisionType == Events::collisionTypes::mapChanger){
        if ((topLimit >= entryTopLimit && topLimit <= entryBottomLimit) || (bottomLimit <= entryBottomLimit && bottomLimit >= entryTopLimit)) {
            std::cout << "map change collision!" << std::endl;
            entityCollision = true;
            { //if collision with jumper happens, go to specific map
                SDL_Event sdl_event;
                sdl_event.type = static_cast<Uint32>(33335);
                auto idPointer = new int;
                *idPointer = entry.first;
                sdl_event.user.data1 = idPointer;
                SDL_PushEvent(&sdl_event);
            }
        }
    } else {
        if ((topLimit >= entryTopLimit && topLimit <= entryBottomLimit) || (bottomLimit <= entryBottomLimit && bottomLimit >= entryTopLimit)) {
            std::cout << "collision!" << std::endl;
            entityCollision = true;
            mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
        }
    }

    return entityCollision;

}
