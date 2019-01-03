//
// Created by armin on 30.12.18.
//

#include <iostream>
#include "CollisionSystem.h"
#include "../events/EntityMoved.h"
#include "../events/CollisionEvent.h"
#include "../managers/ComponentsManager.h"
#include "../managers/EntityManager.h"
#include "../MapParser.h"

Systems::CollisionSystem::CollisionSystem(Managers::EventsManager *pEventsmanager):mEventsManager(pEventsmanager) {

    std::function<void(const std::shared_ptr<Events::Event>&)> callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::EntityMoved*>(pEvent.get());
        auto entityId = event->mEntityId;
        auto collideAbles = Managers::ComponentsManager::getCollideAble();

        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = Managers::ComponentsManager::getVisualComponent(entityId);

        int rightLimit = visual->mImageRect.w + spatial->mPositionX;
        int leftLimit = spatial->mPositionX;
        int topLimit = spatial->mPositionY;
        int bottomLimit = spatial->mPositionY + visual->mImageRect.h;

        //maskCollision

        bool maskCollision = false;
        int maskRightLimit = (int) ceil((double)rightLimit/50.0);
        int maskLeftLimit = (int) ceil((double)leftLimit/50.0);
        int maskTopLimit = (int) ceil((double)topLimit/50.0);
        int maskBottomLimit = (int) ceil((double)bottomLimit/50.0);

        for (int horizontal = maskLeftLimit-1; horizontal < maskRightLimit; horizontal++) {
            for (int vertical = maskTopLimit-1; vertical < maskBottomLimit; vertical++) {
                if ((system->collisionMask->at(static_cast<unsigned long>(horizontal + vertical * system->mapWidth))) == true) {
                    std::cout << "collision via mask detected" << std::endl;
                    maskCollision = true;
                    system->mEventsManager->addEvent(
                            std::make_shared<Events::CollisionEvent>(entityId, 0, Events::collisionTypes::regular));
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
                    }
                    case Entities::entityTypes::none: {

                    }
                }

                if (leftLimit > entryLeftLimit && leftLimit < entryRightLimit) {
                    if (topLimit > entryTopLimit && topLimit < entryBottomLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                    } else if (bottomLimit < entryBottomLimit && bottomLimit > entryTopLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                    }
                } else if (rightLimit < entryRightLimit && rightLimit > entryLeftLimit) {
                    if (topLimit > entryTopLimit && topLimit < entryBottomLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                    } else if (bottomLimit < entryBottomLimit && bottomLimit > entryTopLimit) {
                        system->mEventsManager->addEvent(std::make_shared<Events::CollisionEvent>(entityId, entry.first, collisionType));
                        std::cout << "collision!" << std::endl;
                    }
                }
            }
        }

    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityMoved, callback);
}

void Systems::CollisionSystem::changeCollisionMask(std::vector<bool> *collisionMask) {
    this->collisionMask = collisionMask;

    auto mask = this->collisionMask;
    MapParser::printCollisionMask(*mask, 54);
}

void Systems::CollisionSystem::changeMapWidth(int width) {
    mapWidth = width;
}