//
// Created by armin on 26.12.18.
//

#ifndef GAME_VISUALCOMPONENT_H
#define GAME_VISUALCOMPONENT_H

#include <SDL_rect.h>
#include <SDL_system.h>
#include <memory>
#include "Component.h"

namespace Components {
    class VisualComponent: public Component {
    public:
        VisualComponent(const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH);
        std::shared_ptr<SDL_Texture> mTexture;
        SDL_Rect mImageRect;
    };
}


#endif //GAME_VISUALCOMPONENT_H
