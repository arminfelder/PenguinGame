//
// Created by armin on 16.01.19.
//

#ifndef GAME_INVENTORYSYSTEM_H
#define GAME_INVENTORYSYSTEM_H

#include <SDL_render.h>
#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class InventorySystem: public System {
    public:
        InventorySystem(SDL_Renderer *pPrenderer,Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager;
        std::shared_ptr<SDL_Texture> textureDoubleJump;
        std::shared_ptr<SDL_Texture> textureKey2;
    };
}


#endif //GAME_INVENTORYSYSTEM_H
