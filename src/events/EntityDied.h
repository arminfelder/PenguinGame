//
// Created by armin on 22.01.19.
//

#ifndef GAME_ENTITYDIED_H
#define GAME_ENTITYDIED_H

#include <SDL_rect.h>
#include "Event.h"
#include "../components/Inventory.h"

namespace Events {
    class EntityDied:public Event {
    public:
        EntityDied(int pEntity, int pOrigHealth, SDL_Point pPosition, const std::shared_ptr<Components::Inventory> &pInventory);
        int mEntity;
        int mOrigHealth;
        SDL_Point mPosition;
        std::shared_ptr<Components::Inventory> mInventory;
    };
}


#endif //GAME_ENTITYDIED_H
