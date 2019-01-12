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

Systems::PhysicsSystem::PhysicsSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::FallingEvent*>(pEvent.get());
        auto entityId = event->mEntityId;
        auto momentum = Managers::ComponentsManager::getMomentumComponent(entityId);
        //momentum->gravitation = 10;
        momentum->speedY = 10;
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::Falling,callback);
}

void Systems::PhysicsSystem::update(uint64_t) {
    //todo rename that silly stuff
    auto momenta = Managers::ComponentsManager::getMomenta();
    for(const auto &entry:momenta){
        auto moveEvent = std::make_shared<Events::MoveEntity>(entry.first,entry.second->speedX,entry.second->speedY);
        mEventsManager->addEvent(moveEvent);
    }
}
