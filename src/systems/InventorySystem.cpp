//
// Created by armin on 16.01.19.
//

#include "InventorySystem.h"
#include "../events/CollisionEvent.h"
#include "../managers/ComponentsManager.h"
#include "../events/EntityDied.h"
#include "../managers/EntityManager.h"
#include "../entities/DoubleJumpEnabler.h"
#include "../entities/Key.h"

using namespace Systems;
InventorySystem::InventorySystem(SDL_Renderer *pRenderer, Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto collisionCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());

        if(event->mType == Events::collisionTypes::keyArea2){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            if (inventory && canCollect) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::keyArea2) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::keyArea2);
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }
        }else if(event->mType == Events::collisionTypes::key){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            auto canOpen = Managers::ComponentsManager::getCanOpen(event->mCollidingEntity);

            if(canOpen&&canCollect&&inventory) {
                Components::Inventory::ItemTypes item;
                if (canOpen->mOpens == Components::CanOpen::Areas::area1) {
                    item = Components::Inventory::ItemTypes::keyArea1;
                } else if (canOpen->mOpens == Components::CanOpen::Areas::area2) {
                    item = Components::Inventory::ItemTypes::keyArea2;
                }

                if (inventory && canCollect) {
                    if (canCollect->mTypes.find(item) != canCollect->mTypes.end()) {
                        inventory->addItem(item);
                        Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                    }
                }
            }
        }else if(event->mType == Events::collisionTypes::ak47){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            auto xp = Managers::ComponentsManager::getXp(1);
            if (inventory && canCollect &&& xp && xp->mXp>10) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::ak47) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::ak47);
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }
        }
        else if (event->mType == Events::collisionTypes::disc) {
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            if (inventory && canCollect) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::disc) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::disc);
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }
        }else if(event->mType == Events::collisionTypes::shield){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            auto evadeCap = Managers::ComponentsManager::getEvadeCapability(event->mMovingEntity);
            if (inventory && canCollect&&evadeCap) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::shield) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::shield);
                    if(evadeCap){
                        evadeCap->mChance += 10;
                    }
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }
        }else if(event->mType == Events::collisionTypes::doubleJump){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            auto moveable = Managers::ComponentsManager::getMoveableComponent(event->mMovingEntity);
            if (inventory && canCollect) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::shield) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::doubleJump);
                    if(moveable){
                        moveable->canDoubleJump = true;
                    }
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }
        }
    };

    auto entityDiedCallback = [system=this] (const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::EntityDied*>(pEvent.get());
        auto inventory = event->mInventory;
        if(inventory){
            for(const auto &dropable: inventory->mDropables){
                if(inventory->hasItem(dropable)) {
                    switch (dropable){
                        case Components::Inventory::ItemTypes::doubleJump:{
                            int entityId = Managers::EntityManager::createEntity<Entities::DoubleJumpEnabler>();
                            Managers::ComponentsManager::createVisualComponent(entityId, system->textureDoubleJump, 50,50);
                            Managers::ComponentsManager::createSpatialComponent(entityId, event->mPosition.x, event->mPosition.y);
                            Managers::ComponentsManager::createCollideAbleComponent(entityId);
                            break;
                        }
                        case Components::Inventory::ItemTypes::keyArea1:{
                            int entityId = Managers::EntityManager::createEntity<Entities::Key>();
                            Managers::ComponentsManager::createVisualComponent(entityId, system->textureKey2, 50,50);
                            Managers::ComponentsManager::createSpatialComponent(entityId, event->mPosition.x, event->mPosition.y);
                            Managers::ComponentsManager::createCollideAbleComponent(entityId);
                            Managers::ComponentsManager::createCanOpen(entityId, Components::CanOpen::Areas::area1);
                            break;
                        }
                        case Components::Inventory::ItemTypes::keyArea2:{
                            int entityId = Managers::EntityManager::createEntity<Entities::Key>();
                            Managers::ComponentsManager::createVisualComponent(entityId, system->textureKey2, 50,50);
                            Managers::ComponentsManager::createSpatialComponent(entityId, event->mPosition.x, event->mPosition.y);
                            Managers::ComponentsManager::createCollideAbleComponent(entityId);
                            Managers::ComponentsManager::createCanOpen(entityId, Components::CanOpen::Areas::area2);
                            break;
                        }
                        default:break;
                    }
                }
            }
        }
    };


    std::shared_ptr<SDL_Surface> imageDoubleJump(SDL_LoadBMP("./res/doubleJump.bmp"), SDL_FreeSurface);
    textureDoubleJump = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageDoubleJump.get()), SDL_DestroyTexture);


    std::shared_ptr<SDL_Surface> imageKey(SDL_LoadBMP("./res/secret_key.bmp"), SDL_FreeSurface);
    textureKey2 = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageKey.get()), SDL_DestroyTexture);


    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, collisionCallback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityDied, entityDiedCallback);
}
