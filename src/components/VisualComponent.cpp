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


#include "VisualComponent.h"

using namespace Components;

VisualComponent::VisualComponent(const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH) {
    mTexture = pTexture;
    mImageRect.h = pSizeH;
    mImageRect.w = pSizeW;
}

VisualComponent::VisualComponent(
        const std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> &pTexture, int pSizeW,
        int pSizeH) {

    auto pos = pTexture->find("default");
    mTextureMap = pTexture;
    mTexture = pos->second[0];
    mImageRect.h = pSizeH;
    mImageRect.w = pSizeW;
}
