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
        auto moveable = Managers::ComponentsManager::getMoveableComponent(1);

        switch (event->mKeyCode.sym){
            case SDLK_UP:
                if(moveable->canMoveUp) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionY -= 10;
                }
                break;
            case SDLK_RIGHT:
                if(moveable->canMoveRight) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionX += 10;
                }
                break;
            case SDLK_DOWN:
                if(moveable->canMoveDown) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionY += 10;
                }
                break;
            case SDLK_LEFT:
                if(moveable->canMoveLeft) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionX -= 10;
                }
                break;
            default:
                break;
        }

    };
    mEventsManager->regsiterEventHandler(Events::EventTypes::Input, callback );
}
