//
// Created by armin on 12.01.19.
//

#include "TriggerSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyDownEvent.h"
#include "../events/KeyUpEvent.h"
#include "../managers/ComponentsManager.h"

using namespace Systems;
TriggerSystem::TriggerSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto keyPressedCallback = [system=this](const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::KeyPressedEvent*>(pEvent.get());
        if(event->mKeyCode.sym == SDLK_KP_ENTER){
            auto inventory = Managers::ComponentsManager::getInventory(1);
            auto playerPosition = Managers::ComponentsManager::getSpatialComponent(1);
            auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);

            if(inventory){
                auto useables = Managers::ComponentsManager::getUseables();
                for(const auto &useable: useables){
                    auto spatial = Managers::ComponentsManager::getSpatialComponent(useable.first);
                    auto visual = Managers::ComponentsManager::getVisualComponent(useable.first);
                    if ((playerPosition->mPositionX+playerVisual->mImageRect.w) == spatial->mPositionX){
                        //if(playerPosition->mPositionY+playerVisual->)
                    }
                }
            }
        }
    };
}
