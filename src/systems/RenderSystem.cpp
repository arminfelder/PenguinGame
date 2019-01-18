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


#include <SDL_timer.h>
#include <iostream>
#include "RenderSystem.h"
#include "../managers/ComponentsManager.h"
#include "../components/CameraOffset.h"
#include "../events/EntityMoved.h"


Systems::RenderSystem::RenderSystem(SDL_Window *pWindow, SDL_Renderer *pPrenderer, Managers::EventsManager *pEventsManager):
mWindow(pWindow),mRenderer(pPrenderer),mEventsManager(pEventsManager){
    mWindow = pWindow;
    mRenderer = pPrenderer;

    auto callback = [system = this] (const std::shared_ptr<Events::Event> &pEvent) {
        auto movementElement = static_cast<Events::EntityMoved*>(pEvent.get());
        if (movementElement->mEntityId != 1)
            return;//aka player did not move moved

        int height, width;
        SDL_GetWindowSize(system->mWindow, &width, &height);

        //TODO: refactor
        auto cameraPositions = Managers::ComponentsManager::getCameraOffsets();
        auto firstCam = cameraPositions.begin()->second;

        auto playerPositon = Managers::ComponentsManager::getSpatialComponent(1);
        auto playerY = playerPositon->mPositionY + firstCam->yOffset;
        auto playerX = playerPositon->mPositionX + firstCam->xOffset;

        auto sectorX = std::ceil(playerX/ static_cast<double>(width));
        auto sectorY = std::ceil(playerY/ static_cast<double>(height));

        auto cameraMoveOffset = 0.05;
        auto maxOffsetX = width * cameraMoveOffset;
        auto maxOffsetY = height * cameraMoveOffset;

        //test if camera is way off (happens when using the teleporter)
        auto cameraOffsetSectorX = std::ceil(firstCam->xOffset / static_cast<double>(width));
        auto cameraOffsetSectorY = std::ceil(firstCam->yOffset / static_cast<double>(height));


/*        while (playerY > height*0.8*(cameraOffsetSectorY+1)) {
            firstCam->yOffset += height * 0.8;
            cameraOffsetSectorY = std::ceil(firstCam->yOffset / static_cast<double>(height));
        }*/

        //move camera left
        if (((sectorX - 1)*width + maxOffsetX) > playerX)
            firstCam->xOffset+=width*0.8;
        //move camera right
        else if ((sectorX * width - maxOffsetX) < playerX)
            firstCam->xOffset-=width*0.8;
        //move camera down
        if (((sectorY - 1)*height + maxOffsetY) > playerY)
            firstCam->yOffset+=height*0.8;
        //move camera up
        else if ((sectorY * height - maxOffsetY) < playerY)
            firstCam->yOffset-=height*0.8;



    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityMoved, callback);

    std::shared_ptr<SDL_Surface> imageBG(SDL_LoadBMP("./res/the-background-2819000.bmp"), SDL_FreeSurface);
    mGameBackground = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(mRenderer, imageBG.get()), SDL_DestroyTexture);


}

Systems::RenderSystem::~RenderSystem() {

}

void Systems::RenderSystem::update(uint64_t pTimeDiff) {

    auto visualComponents = Managers::ComponentsManager::getVisualComponents();
    auto cameraPositions = Managers::ComponentsManager::getCameraOffsets();
    auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
    auto firstCam = cameraPositions.begin()->second;


    Components::CameraOffset offset(0,0);

    SDL_RenderClear(mRenderer);

    SDL_Rect rect{static_cast<int>(0+playerSpatial->mPositionX*0.1), static_cast<int>(0+playerSpatial->mPositionY*0.1),1500,800};
    SDL_Point origin{0,0};
    SDL_Rect fill{0,0,0,0};
    SDL_GetWindowSize(mWindow, &fill.w, &fill.h);


    SDL_RenderCopyEx(mRenderer, mGameBackground.get() , &rect, &fill , 0,nullptr , SDL_FLIP_NONE);


    std::map<int, std::shared_ptr<Components::VisualComponent>>::reverse_iterator revIter;

    for(revIter = visualComponents.rbegin(); revIter!=visualComponents.rend(); revIter++){
        int entityId = revIter->first;
        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = revIter->second;

        SDL_Rect dstrect = visual->mImageRect;
        if(spatial->moveWithMap) {
            dstrect.x = spatial->mPositionX + firstCam->getXOffset();
            dstrect.y = spatial->mPositionY + firstCam->getYOffset();
        }else{
            dstrect.x = spatial->mPositionX;
            dstrect.y = spatial->mPositionY;
        }
        SDL_Point center;
        center.x= 0;
        center.y = 0;
        SDL_RenderCopyEx(mRenderer, visual->mTexture.get() , nullptr, &dstrect,visual->mRotateAngle, nullptr, visual->mFlip);
    }

    SDL_RenderPresent(mRenderer);

}


void Systems::RenderSystem::setWindow(SDL_Window *pWindow) {
    mWindow = pWindow;
}

void Systems::RenderSystem::setRendered(SDL_Renderer *pRenderer) {
    mRenderer = pRenderer;
}
