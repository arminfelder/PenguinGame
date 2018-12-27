//
// Created by armin on 26.12.18.
//

#ifndef GAME_VISUALCOMPONENT_H
#define GAME_VISUALCOMPONENT_H

#include <SDL_rect.h>
#include <SDL_system.h>
#include "Component.h"

namespace Components {
    class VisualComponent: public Component {
    public:
        VisualComponent(SDL_Texture* pTexture, int pSizeW, int pSizeH);
        SDL_Texture *mTexture = nullptr;
        SDL_Rect mImageRect;
    };
}


#endif //GAME_VISUALCOMPONENT_H
