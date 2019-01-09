//
// Created by armin on 26.12.18.
//

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

}

Systems::RenderSystem::~RenderSystem() {

}

void Systems::RenderSystem::update(uint64_t pTimeDiff) {

    auto visualComponents = Managers::ComponentsManager::getVisualComponents();
    auto cameraPositions = Managers::ComponentsManager::getCameraOffsets();
    auto firstCam = cameraPositions.begin()->second;


    Components::CameraOffset offset(0,0);

    SDL_RenderClear(mRenderer);

    std::map<int, std::shared_ptr<Components::VisualComponent>>::reverse_iterator revIter;

    for(revIter = visualComponents.rbegin(); revIter!=visualComponents.rend(); revIter++){
        int entityId = revIter->first;
        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = revIter->second;

        SDL_Rect dstrect = visual->mImageRect;
        dstrect.x = spatial->mPositionX + firstCam->getXOffset();
        dstrect.y = spatial->mPositionY+ firstCam->getYOffset();

        SDL_Point center;
        center.x= 0;
        center.y = 0;
        SDL_RenderCopyEx(mRenderer, visual->mTexture.get() , nullptr, &dstrect,visual->mRotateAngle, &center, visual->mFlip);
    }

    SDL_RenderPresent(mRenderer);

}


void Systems::RenderSystem::setWindow(SDL_Window *pWindow) {
    mWindow = pWindow;
}

void Systems::RenderSystem::setRendered(SDL_Renderer *pRenderer) {
    mRenderer = pRenderer;
}
