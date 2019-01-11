//
// Created by armin on 10.01.19.
//

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
