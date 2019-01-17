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


#ifndef GAME_SYSTEMSMANAGER_H
#define GAME_SYSTEMSMANAGER_H

#include "../systems/HealthSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/PositionSystem.h"
#include "../systems/InputSystem.h"
#include "../managers/EventsManager.h"
#include "../systems/CollisionSystem.h"
#include "../systems/AudioSystem.h"
#include "../systems/TextureSystem.h"
#include "../systems/PhysicsSystem.h"
#include "../systems/AiSystem.h"
#include "../systems/CombatSystem.h"
#include "../systems/InventorySystem.h"
#include "../systems/TriggerSystem.h"

namespace Managers {

    class SystemsManager {
    public:

        SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer, EventsManager *pEventsManager);
        void sendEvent();

        void update(uint64_t pTimeDiff);

        Systems::HealthSystem *getMHealthSystem() const;

        Systems::RenderSystem *getMRenderSystem() const;

        Systems::CollisionSystem *getCollisionSystem() const;

    private:
        Systems::RenderSystem* mRenderSystem = nullptr;
        Systems::HealthSystem* mHealthSystem = nullptr;
        Systems::PositionSystem* mPositionSystem = nullptr;
        Systems::InputSystem* mInputSystem = nullptr;
        Systems::CollisionSystem* mCollisionSystem = nullptr;
        Systems::AudioSystem* mAudioSystem = nullptr;
        Systems::TextureSystem* mTextureSystem = nullptr;
        Systems::PhysicsSystem* mPhysicsSystem = nullptr;
        Systems::AiSystem* mAiSystem = nullptr;
        Systems::CombatSystem* mCombatSystem = nullptr;
        Systems::InventorySystem* mInvetorySystem = nullptr;
        Systems::TriggerSystem* mTriggerSystem = nullptr;
        Managers::EventsManager* mEventsManager = nullptr;



    };
}

#endif //GAME_SYSTEMSMANAGER_H
