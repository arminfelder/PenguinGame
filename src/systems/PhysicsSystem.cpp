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
        momentum->gravitation = 2;
        momentum->speedY +=momentum->gravitation;
        if (momentum->speedY >= 12)
            momentum->speedY = 12;
    };

    //jumping
    auto callbackKeyUp = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::KeyUpEvent*>(pEvent.get());
        if(event->mKeyCode.sym == SDLK_SPACE){
            auto momentum = Managers::ComponentsManager::getMomentumComponent(1);
            if (momentum->speedY == 0)
                momentum->speedY -= 15;
        }
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::Falling,callback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::KeyUp, callbackKeyUp);
}

void Systems::PhysicsSystem::update(uint64_t pTimeDiff) {
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
