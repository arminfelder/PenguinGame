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


#ifndef GAME_VISUALCOMPONENT_H
#define GAME_VISUALCOMPONENT_H

#include <SDL_rect.h>
#include <SDL_system.h>
#include <vector>
#include <map>
#include <memory>
#include "Component.h"

namespace Components {
    class VisualComponent: public Component {
    public:
        VisualComponent(const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH);
        VisualComponent(const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTexture, int pSizeW, int pSizeH);
        std::shared_ptr<SDL_Texture> mTexture;
        std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> mTextureMap;
        SDL_Rect mImageRect;
        int curImgPos = 0;
        SDL_RendererFlip mFlip = SDL_FLIP_NONE;
        int mRotateAngle = 0;
    };
}


#endif //GAME_VISUALCOMPONENT_H
