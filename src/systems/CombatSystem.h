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


#ifndef GAME_COMBATSYSTEM_H
#define GAME_COMBATSYSTEM_H

#include <SDL_render.h>
#include "System.h"
#include "../managers/EventsManager.h"
#include "../components/Inventory.h"

namespace Systems {
    class CombatSystem:public System {
    public:
        CombatSystem(SDL_Renderer *pRenderer,Managers::EventsManager *pEventsManager);
        void attackWithItem(const Components::Inventory::ItemTypes &pItem);

    private:
        Managers::EventsManager *mEventsManager;
        std::shared_ptr<SDL_Texture> mBlueBullet;
        std::shared_ptr<SDL_Texture> mAkBulletLeft;
        std::shared_ptr<SDL_Texture> mAkBulletRight;
        std::shared_ptr<SDL_Texture> mTextureHandRight;
        std::shared_ptr<SDL_Texture> mTextureHandLeft;
        int calculateLevel(int xp);

    };
}


#endif //GAME_COMBATSYSTEM_H
