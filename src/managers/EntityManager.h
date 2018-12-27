//
// Created by armin on 14.12.18.
//

#ifndef GAME_ENTITYMANAGER_H
#define GAME_ENTITYMANAGER_H

#include <memory>
#include <unordered_map>
#include "../entities/Entity.h"

namespace Managers {

    class EntityManager {
    public:
        int createEntity();

        bool destroyEntity(int pId);

        std::shared_ptr<Entities::Entity> getEntity(int pId);

    private:
        int mCurrEntityIndex = 1;
        std::unordered_map<int, std::shared_ptr<Entities::Entity>> mEntities;
    };
}

#endif //GAME_ENTITYMANAGER_H
