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
                        visual->curImgPos = (visual->curImgPos+1)%static_cast<int>(pos->second.size());
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
