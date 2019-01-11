//
// Created by armin on 29.12.18.
//

#include "PositionSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/EntityMoved.h"
#include "../managers/ComponentsManager.h"
#include "../events/CollisionEvent.h"
#include "../events/HealthEvent.h"
#include "../events/MoveEntity.h"

Systems::PositionSystem::PositionSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::KeyUpEvent*>(pEvent.get());
        auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
        auto moveable = Managers::ComponentsManager::getMoveableComponent(1);

        if (event->getType() != Events::EventTypes::KeyUp) {
            switch (event->mKeyCode.sym) {
                case SDLK_UP:
                    if (moveable->canMoveUp) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionY -= 10;

                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::up));
                    }
                    break;
                case SDLK_RIGHT:
                    if (moveable->canMoveRight) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionX += 10;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::right));

                    }
                    break;
                case SDLK_DOWN:
                    if (moveable->canMoveDown) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionY += 10;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::down));
                    }
                    break;
                case SDLK_LEFT:
                    if (moveable->canMoveLeft) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionX -= 10;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::left));
                    }
                    break;
                default:
                    break;
            }
        }
    };

    auto callbackCollision = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());
        if(event->mType == Events::collisionTypes::regular){
            int entity = event->mMovingEntity;
            auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(entity);
            playerSpatial->mPositionX = playerSpatial->mPrevPositionX;
            playerSpatial->mPositionY = playerSpatial->mPrevPositionY;
        }
        auto moveable = Managers::ComponentsManager::getMoveableComponent(1);
        moveable->canMoveRight = true;
        moveable->canMoveLeft = true;
        if(event->mType == Events::collisionTypes::ladder){
            moveable->canMoveDown = true;
            moveable->canMoveUp = true;

        }else if(event->mType == Events::collisionTypes::movementReset){
            moveable->canMoveUp = false;
            moveable->canMoveDown = false;
        }else if(event->mType == Events::collisionTypes::ladderEnd){
            moveable->canMoveUp = false;
            moveable->canMoveDown = true;
        }else if(event->mType == Events::collisionTypes::ladderBegin){
            moveable->canMoveUp = true;
            moveable->canMoveDown = true;
        }
    };

    auto moveEventCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::MoveEntity*>(pEvent.get());

        auto spatial = Managers::ComponentsManager::getSpatialComponent(event->mEntityId);
        spatial->mPositionX += event->mX;
        spatial->mPositionY += event->mY;
        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::down));
        

    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::KeyUp, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::KeyDown, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, callbackCollision);
    mEventsManager->regsiterEventHandler(Events::EventTypes::MoveEntity, moveEventCallback);
}
