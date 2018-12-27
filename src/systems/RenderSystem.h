//
// Created by armin on 26.12.18.
//

#ifndef GAME_RENDERSYSTEM_H
#define GAME_RENDERSYSTEM_H

#include <SDL_video.h>
#include <SDL_system.h>

#include "System.h"

namespace Systems {
    class RenderSystem: public System {
    public:
        RenderSystem(SDL_Window *pWindow, SDL_Renderer *pPrenderer);
        void setWindow(SDL_Window *pWindow);
        void setRendered(SDL_Renderer *pRenderer);
        ~RenderSystem();

        void update(float pTimeDiff);

    private:
        SDL_Window *mWindow = nullptr;
        SDL_Renderer *mRenderer = nullptr;
        SDL_Texture *mTestTexture = nullptr;

    };
}


#endif //GAME_RENDERSYSTEM_H
