//
// Created by armin on 14.12.18.
//

#ifndef GAME_COMPONENTSMANAGER_H
#define GAME_COMPONENTSMANAGER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include "../components/Component.h"
#include "../components/Health.h"
#include "../components/Position.h"
#include "../entities/Entity.h"
#include "../components/VisualComponent.h"
#include "../components/SpatialComponent.h"

namespace Managers {

    class ComponentsManager {
    public:
        static std::unordered_map<int, std::shared_ptr<Components::Health>> &getHealthComponents();
        static std::unordered_map<int, std::shared_ptr<Components::VisualComponent>> &getVisualComponents();
        static std::unordered_map<int, std::shared_ptr<Components::SpatialComponent>> &getSpatialComponents();

        static std::shared_ptr<Components::Health> &getHealthComponent(int pEntityId);
        static std::shared_ptr<Components::VisualComponent> &getVisualComponent(int pEntityId);
        static std::shared_ptr<Components::SpatialComponent> &getSpatialComponent(int pEntityId);

        static void createHealthComponent(int pEntityId, int pHp = 100);
        static void createVisualComponent(int pEntityId, SDL_Texture* pTexture, int pSizeW, int pSizeH);
        static void createSpatialComponent(int pEntityId, int pPositionX, int pPositionY);


        bool createComponent();

    private:
        static std::unordered_map<int, std::shared_ptr<Components::Health>> mHealthComponents;
        static std::unordered_map<int, std::shared_ptr<Components::VisualComponent>> mVisualComponents;
        static std::unordered_map<int, std::shared_ptr<Components::SpatialComponent>> mSpatialComponents;

    };
}

#endif //GAME_COMPONENTSMANAGER_H
