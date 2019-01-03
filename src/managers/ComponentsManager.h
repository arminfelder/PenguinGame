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
#include "../components/MoveAbleComponent.h"
#include "../components/CollideAble.h"
#include "../components/CameraOffset.h"
#include "../components/Momentum.h"

namespace Managers {

    class ComponentsManager {
    public:
        static std::map<int, std::shared_ptr<Components::Health>> &getHealthComponents();
        static std::map<int, std::shared_ptr<Components::VisualComponent>> &getVisualComponents();
        static std::map<int, std::shared_ptr<Components::SpatialComponent>> &getSpatialComponents();
        static std::map<int, std::shared_ptr<Components::MoveAbleComponent>> &getMoveableComponents();
        static std::map<int, std::shared_ptr<Components::CollideAble>> &getCollideAble();
        static std::map<int, std::shared_ptr<Components::CameraOffset>> &getCameraOffsets();
        static std::map<int, std::shared_ptr<Components::Momentum>> &getMomentums();

        static std::shared_ptr<Components::Health> &getHealthComponent(int pEntityId);
        static std::shared_ptr<Components::VisualComponent> &getVisualComponent(int pEntityId);
        static std::shared_ptr<Components::SpatialComponent> &getSpatialComponent(int pEntityId);
        static std::shared_ptr<Components::MoveAbleComponent> &getMoveableComponent(int pEntityId);
        static std::shared_ptr<Components::CollideAble> &getCollideAble(int pEntityId);
        static std::shared_ptr<Components::CameraOffset> &getCameraOffsetComponent(int pEntityId);
        static std::shared_ptr<Components::Momentum> &getMomentumComponent(int pEntityId);


        static void createHealthComponent(int pEntityId, int pHp = 100);
        static void createVisualComponent(int pEntityId, const std::shared_ptr<SDL_Texture> &pTexture, int pSizeW, int pSizeH);
        static void createSpatialComponent(int pEntityId, int pPositionX, int pPositionY);
        static void createMoveAbleComponent(int pEntityId, bool pRight, bool pDown, bool pLeft, bool pUp);
        static void createCollideAbleComponent(int pEntityId);
        static void createCameraComponent(int pEntityId);
        static void createMomentumComponent(int pEntityId);

    private:
        static std::map<int, std::shared_ptr<Components::Health>> mHealthComponents;
        static std::map<int, std::shared_ptr<Components::VisualComponent>> mVisualComponents;
        static std::map<int, std::shared_ptr<Components::SpatialComponent>> mSpatialComponents;
        static std::map<int, std::shared_ptr<Components::MoveAbleComponent>> mMoveableComponents;
        static std::map<int, std::shared_ptr<Components::CollideAble>> mCollideables;
        static std::map<int, std::shared_ptr<Components::CameraOffset>> mCameraOffset;
        static std::map<int, std::shared_ptr<Components::Momentum>> mMomentum;
    };
}

#endif //GAME_COMPONENTSMANAGER_H
