project(game)
#add_executable(game PenguinGame.cpp PenguinGame.h entities/Entity.cpp entities/Entity.h eventHandler.cpp eventHandler.h World.cpp World.h res_path.h position.cpp position.h Dimension.cpp Dimension.h EntityController.cpp EntityController.h TXTParser.cpp TXTParser.h Map.cpp Map.h components/Component.cpp components/Component.h main.cpp components/Position.cpp components/Position.h components/Health.cpp components/Health.h managers/ComponentsManager.cpp EventsManager.cpp
#        managers/SystemsManager.h   managers/EntityManager.cpp entities/Player.cpp entities/Player.h systems/System.cpp systems/System.h systems/HealthSystem.cpp systems/HealthSystem.h)

add_executable(game main.cpp PenguinGame.cpp PenguinGame.h
        entities/Entity.cpp
        GameEngine.cpp
        systems/RenderSystem.cpp
        systems/InputSystem.cpp
        systems/HealthSystem.cpp
        managers/EntityManager.cpp
        managers/SystemsManager.cpp
        managers/ComponentsManager.cpp
        components/VisualComponent.cpp
        components/SpatialComponent.cpp
        components/Health.cpp
        events/Event.cpp
        events/KeyPressedEvent.cpp
        events/KeyUpEvent.cpp
        events/KeyDownEvent.cpp
        managers/EventsManager.cpp
        events/HealthEvent.cpp events/HealthEvent.h systems/PositionSystem.cpp systems/PositionSystem.h events/EntityMoved.cpp events/EntityMoved.h)
target_link_libraries(game ${SDL2_LIBRARIES})
