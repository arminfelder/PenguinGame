//
// Created by armin on 20.12.18.
//

#include "SystemsManager.h"

using namespace Managers;
using namespace Systems;

SystemsManager::SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer) {
    mHealthSystem = new HealthSystem;
    mRenderSystem = new RenderSystem(pWindow,pPrenderer);
}

void SystemsManager::sendEvent() {

}

HealthSystem *SystemsManager::getMHealthSystem() const {
    return mHealthSystem;
}

RenderSystem *SystemsManager::getMRenderSystem() const {
    return mRenderSystem;
}

void SystemsManager::update(float pTimeDiff) {
    mRenderSystem->update(pTimeDiff);
}
