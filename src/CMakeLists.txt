project(game)
#add_executable(game PenguinGame.cpp PenguinGame.h entities/Entity.cpp entities/Entity.h eventHandler.cpp eventHandler.h World.cpp World.h res_path.h position.cpp position.h Dimension.cpp Dimension.h EntityController.cpp EntityController.h TXTParser.cpp TXTParser.h Map.cpp Map.h components/Component.cpp components/Component.h main.cpp components/Position.cpp components/Position.h components/Health.cpp components/Health.h managers/ComponentsManager.cpp EventsManager.cpp
#        managers/SystemsManager.h   managers/EntityManager.cpp entities/Player.cpp entities/Player.h systems/System.cpp systems/System.h systems/HealthSystem.cpp systems/HealthSystem.h)

add_executable(game main.cpp PenguinGame.cpp PenguinGame.h
        entities/Entity.cpp
        entities/Player.cpp
        entities/Wall.cpp
        entities/Ladder.cpp
        entities/MovementReset.cpp
        entities/LadderEnd.cpp
        entities/LadderBegin.cpp
        entities/HealthIndicator.cpp
        entities/HealthIndicator.h
        GameEngine.cpp
        systems/RenderSystem.cpp
        systems/InputSystem.cpp
        systems/HealthSystem.cpp
        systems/PositionSystem.cpp
        systems/CollisionSystem.cpp
        managers/EntityManager.cpp
        managers/SystemsManager.cpp
        managers/ComponentsManager.cpp
        managers/EventsManager.cpp
        components/VisualComponent.cpp
        components/SpatialComponent.cpp
        components/Health.cpp
        components/MoveAbleComponent.cpp
        components/CollideAble.cpp
        components/CameraOffset.cpp
        events/Event.cpp
        events/KeyPressedEvent.cpp
        events/KeyUpEvent.cpp
        events/KeyDownEvent.cpp
        events/HealthEvent.cpp
        events/EntityMoved.cpp
        events/CollisionEvent.cpp
        events/MapMovement.cpp
        MapParser.cpp
        systems/AudioSystem.cpp systems/AudioSystem.h systems/TextureSystem.cpp systems/TextureSystem.h components/Gravity.cpp components/Gravity.h systems/PhysicsSystem.cpp systems/PhysicsSystem.h)
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
