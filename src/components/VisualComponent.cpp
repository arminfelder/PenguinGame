//
// Created by armin on 26.12.18.
//

#include "VisualComponent.h"

using namespace Components;

VisualComponent::VisualComponent(const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH) {
    mTexture = pTexture;
    mImageRect.h = pSizeH;
    mImageRect.w = pSizeW;
}
