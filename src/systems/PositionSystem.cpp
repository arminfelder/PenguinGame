//
// Created by armin on 29.12.18.
//

#include "PositionSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../managers/ComponentsManager.h"

Systems::PositionSystem::PositionSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    std::function<void(std::shared_ptr<Events::Event>)> callback = [system = this](std::shared_ptr<Events::Event> pEvent)->void {
        auto event = static_cast<Events::KeyUpEvent*>(pEvent.get());
        auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
        playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
        playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
        switch (event->mKeyCode.sym){
            case SDLK_UP:
                playerSpatial->mPositionY -= 10;
                break;
            case SDLK_RIGHT:
                playerSpatial->mPositionX += 10;
                break;
            case SDLK_DOWN:
                playerSpatial->mPositionY += 10;
                break;
            case SDLK_LEFT:
                playerSpatial->mPositionX -= 10;
                break;
        }

    };
    mEventsManager->regsiterEventHandler(Events::EventTypes::Input, callback );
}
