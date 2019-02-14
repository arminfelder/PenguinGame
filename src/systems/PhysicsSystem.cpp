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
#include "PhysicsSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/EntityMoved.h"
#include "../events/FallingEvent.h"
#include "../events/MoveEntity.h"
#include "../events/KeyUpEvent.h"

Systems::PhysicsSystem::PhysicsSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    //falling
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::FallingEvent*>(pEvent.get());
        auto entityId = event->mEntityId;
        auto momentum = Managers::ComponentsManager::getMomentumComponent(entityId);
        if(momentum) {
            momentum->gravitation = 2;
            momentum->speedY += momentum->gravitation;
            if (momentum->speedY >= 12)
                momentum->speedY = 12;
            if (momentum->speedY == 0)
                momentum->speedY += momentum->gravitation;
        }
    };

    //jumping
    auto callbackKeyUp = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        //only allow jumping if not at a ladder
        if (Managers::ComponentsManager::getMoveableComponent(1).get()->climbing)
            return;
        auto event = static_cast<Events::KeyUpEvent*>(pEvent.get());
        if(event->mKeyCode == SDLK_SPACE){
            auto momentum = Managers::ComponentsManager::getMomentumComponent(1);
            auto moveAbleComponent = Managers::ComponentsManager::getMoveableComponent(1);
            if (momentum&&moveAbleComponent&&( momentum->speedY == 0 || (!moveAbleComponent->doubleJumpUsed && moveAbleComponent->canDoubleJump))) { //allow jumping only if user is on ground or has not used double jump (plus is allowed to do so)
                if (momentum->speedY != 0) {//if double jump used, set so
                    moveAbleComponent->doubleJumpUsed = true;
                    std::cout << "old y " << std::to_string(momentum->speedY) <<  std::endl;
                }
                momentum->speedY = -23;
            }

            if(event->mKeys[SDL_SCANCODE_LEFT]){
                momentum->speedX = -5;
            }else if(event->mKeys[SDL_SCANCODE_RIGHT]){
                momentum->speedX = 5;
            }
        }else if((event->mKeyCode == SDLK_RIGHT||event->mKeyCode == SDLK_LEFT) &&event->mKeys[SDL_SCANCODE_SPACE]){
            auto momentum = Managers::ComponentsManager::getMomentumComponent(1);
            auto moveAbleComponent = Managers::ComponentsManager::getMoveableComponent(1);
            if (momentum&&moveAbleComponent&&( momentum->speedY == 0 || (!moveAbleComponent->doubleJumpUsed && moveAbleComponent->canDoubleJump))) { //allow jumping only if user is on ground or has not used double jump (plus is allowed to do so)
                if (momentum->speedY != 0) {//if double jump used, set so
                    moveAbleComponent->doubleJumpUsed = true;
                    std::cout << "old y " << std::to_string(momentum->speedY) <<  std::endl;
                }
                momentum->speedY = -23;
            }

            if(event->mKeyCode == SDLK_LEFT){
                momentum->speedX = -5;
            }else if(event->mKeyCode == SDLK_RIGHT){
                momentum->speedX = 5;
            }
        }
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::Falling,callback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed, callbackKeyUp);
}

void Systems::PhysicsSystem::update(Uint64 pTimeDiff) {
    auto momenta = Managers::ComponentsManager::getMomenta();
    for(const auto &entry:momenta){
        int timeFactor = pTimeDiff/18;
        if(!timeFactor){
            timeFactor = 1;
        }
        int x = entry.second->speedX? static_cast<int>(entry.second->speedX*(timeFactor)):0;
        int y = entry.second->speedY? static_cast<int>(entry.second->speedY*(timeFactor)):0;
        auto moveEvent = std::make_shared<Events::MoveEntity>(entry.first,x,y);
        mEventsManager->addEvent(moveEvent);
    }
}
