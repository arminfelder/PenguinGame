//
// Created by armin on 26.12.18.
//

#include <SDL_timer.h>
#include <iostream>
#include "RenderSystem.h"
#include "../managers/ComponentsManager.h"

Systems::RenderSystem::RenderSystem(SDL_Window *pWindow, SDL_Renderer *pPrenderer, Managers::EventsManager *pEventsManager):
mWindow(pWindow),mRenderer(pPrenderer),mEventsManager(pEventsManager){
    mWindow = pWindow;
    mRenderer = pPrenderer;

}

Systems::RenderSystem::~RenderSystem() {

}

void Systems::RenderSystem::update(uint64_t pTimeDiff) {

    auto visualComponents = Managers::ComponentsManager::getVisualComponents();

    SDL_RenderClear(mRenderer);

    std::map<int, std::shared_ptr<Components::VisualComponent>>::reverse_iterator revIter;

    for(revIter = visualComponents.rbegin(); revIter!=visualComponents.rend(); revIter++){
        int entityId = revIter->first;
        auto spatial = Managers::ComponentsManager::getSpatialComponent(entityId);
        auto visual = revIter->second;

        SDL_Rect dstrect = visual->mImageRect;
        dstrect.x = spatial->mPositionX;
        dstrect.y = spatial->mPositionY;

        SDL_RenderCopy(mRenderer, visual->mTexture , nullptr, &dstrect);
    }

    SDL_RenderPresent(mRenderer);

}


void Systems::RenderSystem::setWindow(SDL_Window *pWindow) {
    mWindow = pWindow;
}

void Systems::RenderSystem::setRendered(SDL_Renderer *pRenderer) {
    mRenderer = pRenderer;
}
