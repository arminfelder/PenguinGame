//
// Created by armin on 10.01.19.
//

#include "PhysicsSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/EntityMoved.h"

Systems::PhysicsSystem::PhysicsSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    std::function<void(const std::shared_ptr<Events::Event>&)> callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
       // auto event = static_cast<Events::EntityMoved>(pEvent);

    };

//    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityMoved)
}

void Systems::PhysicsSystem::update(uint64_t) {
    auto gravities = Managers::ComponentsManager::getGravities();
    for(const auto &entry:gravities){

    }
}
