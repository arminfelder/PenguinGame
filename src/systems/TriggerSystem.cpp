//
// Created by armin on 12.01.19.
//

#include "TriggerSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyDownEvent.h"
#include "../events/KeyUpEvent.h"
#include "../managers/ComponentsManager.h"
#include "../managers/EntityManager.h"
#include "../events/TriggerActivated.h"

using namespace Systems;
TriggerSystem::TriggerSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto keyPressedCallback = [system=this](const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::KeyPressedEvent*>(pEvent.get());
        if(event->mKeyCode.sym == SDLK_RETURN){
            auto inventory = Managers::ComponentsManager::getInventory(1);
            auto playerPosition = Managers::ComponentsManager::getSpatialComponent(1);
            auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);

            int padding = 10;
            int playerLimitRight = playerPosition->mPositionX+playerVisual->mImageRect.w+padding;
            int playerLeftLimit = playerPosition->mPositionX-padding;
            int playerTopLimit = playerPosition->mPositionY-padding;
            int playerBottomLimit = playerPosition->mPositionY+playerVisual->mImageRect.h+padding;

            if(inventory){
                auto useables = Managers::ComponentsManager::getUseables();
                for(const auto &useable: useables){
                    auto spatial = Managers::ComponentsManager::getSpatialComponent(useable.first);
                    auto visual = Managers::ComponentsManager::getVisualComponent(useable.first);
                    int entryRightLimit = spatial->mPositionX+visual->mImageRect.w;
                    int entryLeftLimit = spatial->mPositionX;
                    int entryTopLimit = spatial->mPositionY;
                    int entryBottomLimit = spatial->mPositionY+visual->mImageRect.h;

                    bool collides = false;
                    if (playerLimitRight >= entryLeftLimit &&playerLimitRight<=entryRightLimit){
                        if(playerTopLimit>=entryTopLimit&&playerTopLimit<=entryBottomLimit){
                           collides = true;
                        }else if(playerBottomLimit<=entryBottomLimit && playerBottomLimit>=entryTopLimit){
                            collides = true;
                        }else if(entryBottomLimit<=playerBottomLimit && entryTopLimit>= playerTopLimit){
                            collides = true;
                        }

                    }else if(playerLeftLimit<=entryRightLimit&&playerLeftLimit>=entryLeftLimit){
                        if(playerTopLimit>=entryTopLimit&&playerTopLimit<=entryBottomLimit){
                            collides = true;
                        }else if(playerBottomLimit<=entryBottomLimit && playerBottomLimit>=entryTopLimit){
                            collides = true;
                        }else if(entryBottomLimit<=playerBottomLimit && entryTopLimit>= playerTopLimit){
                            collides = true;
                        }
                    }
                    if(collides){
                        bool requierementsFullFilled = true;
                        for(const auto &cond: useable.second->mRequiresItems){
                            if(!inventory->hasItem(cond)){
                                requierementsFullFilled = false;
                            }
                        }
                        if(requierementsFullFilled){
                            auto entity = Managers::EntityManager::getEntity(useable.first);
                            switch (entity->getType()){
                                case Entities::entityTypes::door :{
                                    Managers::ComponentsManager::getCollideAble().erase(useable.first);
                                    system->mEventsManager->addEvent(std::make_shared<Events::TriggerActivated>(useable.first,1));
                                }
                            }
                        }
                    }
                }
            }
        }
    };
    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed,keyPressedCallback);
}
