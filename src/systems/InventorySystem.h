//
// Created by armin on 16.01.19.
//

#ifndef GAME_INVENTORYSYSTEM_H
#define GAME_INVENTORYSYSTEM_H

#include "System.h"
#include "../managers/EventsManager.h"

namespace Systems {
    class InventorySystem: public System {
    public:
        InventorySystem(Managers::EventsManager *pEventsManager);

    private:
        Managers::EventsManager *mEventsManager;
    };
}


#endif //GAME_INVENTORYSYSTEM_H
