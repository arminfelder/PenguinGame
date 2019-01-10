//
// Created by armin on 26.12.18.
//

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
