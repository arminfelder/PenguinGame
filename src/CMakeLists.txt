project(game)

add_executable(game PenguinGame.cpp PenguinGame.h
        entities/Entity.cpp
        entities/Player.cpp
        entities/Wall.cpp
        entities/Ladder.cpp
        entities/MovementReset.cpp
        entities/LadderEnd.cpp
        entities/LadderBegin.cpp
        entities/HealthIndicator.cpp
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
        components/Momentum.cpp
        events/Event.cpp
        events/KeyPressedEvent.cpp
        events/KeyUpEvent.cpp
        events/KeyDownEvent.cpp
        events/HealthEvent.cpp
        events/EntityMoved.cpp
        events/CollisionEvent.cpp
        events/MapMovement.cpp
        events/FallingEvent.cpp
        MapParser.cpp
        systems/AudioSystem.cpp
        systems/TextureSystem.cpp
        components/Gravity.cpp
        systems/PhysicsSystem.cpp
        main.cpp)

target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
