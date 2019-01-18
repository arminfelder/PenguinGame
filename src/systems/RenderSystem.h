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


#ifndef GAME_RENDERSYSTEM_H
#define GAME_RENDERSYSTEM_H

#include <SDL_video.h>
#include <SDL_system.h>

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class RenderSystem: public System {
    public:
        RenderSystem(SDL_Window *pWindow, SDL_Renderer *pPrenderer, Managers::EventsManager *pEventsManager);
        void setWindow(SDL_Window *pWindow);
        void setRenderer(SDL_Renderer *pRenderer);
        ~RenderSystem();

        void update(uint64_t pTimeDiff);

    private:
        SDL_Window *mWindow = nullptr;
        SDL_Renderer *mRenderer = nullptr;
        SDL_Texture *mTestTexture = nullptr;
        std::shared_ptr<SDL_Texture> mGameBackground;
        Managers::EventsManager *mEventsManager = nullptr;
        std::vector<int> calculateCameraTargetPosition();
        void tryAndMoveCamera();
        void setCameraTargetPosition(std::vector<int> point);
        bool playerIsVisible();

    };
}


#endif //GAME_RENDERSYSTEM_H
