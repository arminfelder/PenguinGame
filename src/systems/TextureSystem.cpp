//
// Created by armin on 09.01.19.
//

#include "TextureSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/EntityMoved.h"

using namespace Systems;

TextureSystem::TextureSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {

    auto walkCallBack = [system = this] (const std::shared_ptr<Events::Event> &pEvent){
        auto movementElement = static_cast<Events::EntityMoved*>(pEvent.get());

        auto entityId = movementElement->mEntityId;
        auto visual = Managers::ComponentsManager::getVisualComponent(entityId);

        switch (movementElement->mDirection){
            case Events::EntityMoved::Direction::up:{
                break;
            }
            case Events::EntityMoved::Direction::down:{
                break;
            };
            case Events::EntityMoved::Direction::left:{
                auto pos = visual->mTextureMap->find("walk");
                if(pos != visual->mTextureMap->end()){
                    if(!pos->second.empty()){
                        visual->curImgPos = visual->curImgPos >0? visual->curImgPos-1:pos->second.size()-1;
                        visual->mTexture = pos->second[visual->curImgPos];
                        visual->mFlip =SDL_FLIP_HORIZONTAL;
                    }
                }
                break;
            };
            case Events::EntityMoved::Direction::right:{
                auto pos = visual->mTextureMap->find("walk");
                if(pos != visual->mTextureMap->end()){
                    if(!pos->second.empty()){
                        visual->curImgPos = (visual->curImgPos+1)%static_cast<int>(pos->second.size());
                        visual->mTexture = pos->second[visual->curImgPos];
                        visual->mFlip =SDL_FLIP_NONE;

                    }
                }
                break;
            };
        }

    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityMoved, walkCallBack);

}
