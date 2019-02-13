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

#include "SystemsManager.h"
#include "../systems/PhysicsSystem.h"

using namespace Managers;
using namespace Systems;

SystemsManager::SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer, EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    mHealthSystem = new HealthSystem(pPrenderer, pEventsManager);
    mPositionSystem = new PositionSystem(pEventsManager);
    mInputSystem = new InputSystem(pEventsManager);
    mCollisionSystem = new CollisionSystem(pEventsManager);
    mAudioSystem = new AudioSystem(pEventsManager);
    mTextureSystem = new TextureSystem(pEventsManager);
    mPhysicsSystem = new PhysicsSystem(pEventsManager);
    mAiSystem = new AiSystem(pEventsManager);
    mCombatSystem = new CombatSystem(pPrenderer, pEventsManager);
    mInvetorySystem = new InventorySystem(pEventsManager);
    mTriggerSystem = new TriggerSystem(pEventsManager);
    mXpSystem = new XpSystem(pPrenderer, pEventsManager);

    mRenderSystem = new RenderSystem(pWindow,pPrenderer,pEventsManager);
}

void SystemsManager::sendEvent() {

}

HealthSystem *SystemsManager::getMHealthSystem() const {
    return mHealthSystem;
}

RenderSystem *SystemsManager::getMRenderSystem() const {
    return mRenderSystem;
}

void SystemsManager::update(Uint64 pTimeDiff) {
    mHealthSystem->update(pTimeDiff);
    mAiSystem->update(pTimeDiff);
    mPhysicsSystem->update(pTimeDiff);
    mInputSystem->update(pTimeDiff);
    mEventsManager->dispatch(pTimeDiff);
    mPositionSystem->update();
    mRenderSystem->update(pTimeDiff);
}

Systems::CollisionSystem *SystemsManager::getCollisionSystem() const {
    return mCollisionSystem;
}

SystemsManager::~SystemsManager() {
    mHealthSystem->~HealthSystem();
    mPositionSystem->~PositionSystem();
    mInputSystem->~InputSystem();
    mCollisionSystem->~CollisionSystem();
    mAudioSystem->~AudioSystem();
    mTextureSystem->~TextureSystem();
    mPhysicsSystem->~PhysicsSystem();
    mAiSystem->~AiSystem();
    mCombatSystem->~CombatSystem();
    mRenderSystem->~RenderSystem();

}

Systems::XpSystem *SystemsManager::getXpSystem() const {
    return mXpSystem;
}
