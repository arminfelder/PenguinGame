//
// Created by armin on 22.12.18.
//

#include "HealthSystem.h"

Systems::HealthSystem::HealthSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    std::function<void(std::shared_ptr<Events::Event>)> callback = [system = this](std::shared_ptr<Events::Event> pEvent)->void {
        auto event = static_cast<Events::HealthEvent*>(pEvent.get());

    };
    mEventsManager->regsiterEventHandler(Events::EventTypes::Health, callback );
}
