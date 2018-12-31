//
// Created by armin on 14.12.18.
//

#ifndef GAME_ENTITYMANAGER_H
#define GAME_ENTITYMANAGER_H

#include <memory>
#include <unordered_map>
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Wall.h"
#include "../entities/Ladder.h"

namespace Managers {

    class EntityManager {
    public:
        EntityManager();
        template <class T>
        static int createEntity(){
            int newIndex = mCurrEntityIndex;
            mEntities.emplace(mCurrEntityIndex, std::make_shared<T>(mCurrEntityIndex));
            mCurrEntityIndex++;
            return newIndex;
        }

        static bool destroyEntity(int pId);

        static std::shared_ptr<Entities::Entity> getEntity(int pId);

    private:
        static int mCurrEntityIndex;
        static std::unordered_map<int, std::shared_ptr<Entities::Entity>> mEntities;
    };
}

#endif //GAME_ENTITYMANAGER_H
