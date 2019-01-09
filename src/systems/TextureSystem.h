//
// Created by armin on 09.01.19.
//

#ifndef GAME_TEXTURESYSTEM_H
#define GAME_TEXTURESYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"


namespace Systems {
    class TextureSystem : public System {
    public:
        TextureSystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager = nullptr;

    };

}


#endif //GAME_TEXTURESYSTEM_H
