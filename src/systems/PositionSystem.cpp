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


#include <SDL_events.h>
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

        int timeFactor = static_cast<int>(system->mEventsManager->mTimediff/18);
        if(!timeFactor){
            timeFactor = 1;
        }
        if (event->getType() != Events::EventTypes::KeyUp) {
            SDL_Event sdl_event;
            switch (event->mKeyCode.sym) {
                case SDLK_UP:
                    if (moveable->canMoveUp) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionY -= 10*timeFactor;

                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::up));
                    }
                    break;
                case SDLK_RIGHT:
                    if (moveable->canMoveRight) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionX += 10*timeFactor;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::right));

                    }
                    break;
                case SDLK_DOWN:
                    if (moveable->canMoveDown) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionY += 10*timeFactor;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::down));
                    }
                    break;
                case SDLK_LEFT:
                    if (moveable->canMoveLeft) {
                        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                        playerSpatial->mPositionX -= 10*timeFactor;
                        system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1,Events::EntityMoved::Direction::left));
                    }
                    break;

                case SDLK_m:
                    sdl_event.type = 32769;
                    SDL_PushEvent(&sdl_event);
                    break;

                case SDLK_p:
                    sdl_event.type = 32770;
                    SDL_PushEvent(&sdl_event);
                    break;

                    //quit game
                case SDLK_ESCAPE:
                    sdl_event.type = SDL_QUIT;
                    SDL_PushEvent(&sdl_event);
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
            moveable->climbing = false;
        }else if(event->mType == Events::collisionTypes::ladderEnd){
            moveable->canMoveUp = false;
            moveable->canMoveDown = true;
            moveable->climbing = true;
        }else if(event->mType == Events::collisionTypes::ladderBegin){
            moveable->canMoveUp = true;
            moveable->canMoveDown = true;
            moveable->climbing = true;
        }else if(event->mType == Events::collisionTypes::teleporterEntry){
            auto targets = Managers::ComponentsManager::getTeleportTargets();
            if(!targets.empty()) {
                auto target = targets.begin()->first;
                auto targetPos = Managers::ComponentsManager::getSpatialComponent(target);

                auto entitySpatial = Managers::ComponentsManager::getSpatialComponent(event->mMovingEntity);
                entitySpatial->mPositionX = targetPos->mPositionX;
                entitySpatial->mPositionY = targetPos->mPositionY;

                system->mEventsManager->addEvent(std::make_shared<Events::MoveEntity>(event->mMovingEntity,1, 1));
            }
        }
    };

    auto moveEventCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::MoveEntity*>(pEvent.get());

        auto spatial = Managers::ComponentsManager::getSpatialComponent(event->mEntityId);
        if(event->mX || event->mY) {
            spatial->mPositionX += event->mX;
            spatial->mPositionY += event->mY;
            Events::EntityMoved::Direction direction;
            if(event->mY >0){
                direction = Events::EntityMoved::Direction::down;
            }else{
                direction = Events::EntityMoved::Direction::up;
            }
            if(event->mEntityId == 1) {
              //  spatial->mPositionX = spatial->mPrevPositionX;
              //  spatial->mPositionY = spatial->mPrevPositionY;
            }
            system->mEventsManager->addEvent(
                    std::make_shared<Events::EntityMoved>(event->mEntityId, direction));
        }

    };


    mEventsManager->regsiterEventHandler(Events::EventTypes::KeyUp, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::KeyDown, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, callbackCollision);
    mEventsManager->regsiterEventHandler(Events::EventTypes::MoveEntity, moveEventCallback);
}
