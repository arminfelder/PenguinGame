###############################################################################
# Copyright (C) Mario Löscher, Armin Felder
# This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
#
# PenguinGame is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PenguinGame is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
##############################################################################


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
        systems/PhysicsSystem.cpp
        systems/AudioSystem.cpp
        systems/TextureSystem.cpp
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
        components/Gravity.cpp
        events/Event.cpp
        events/KeyPressedEvent.cpp
        events/KeyUpEvent.cpp
        events/KeyDownEvent.cpp
        events/HealthEvent.cpp
        events/EntityMoved.cpp
        events/CollisionEvent.cpp
        events/MapMovement.cpp
        events/FallingEvent.cpp
        events/MoveEntity.cpp
        MapParser.cpp
        main.cpp systems/TriggerSystem.cpp systems/TriggerSystem.h entities/HealthItem.cpp entities/HealthItem.h components/Path.cpp components/Path.h entities/Npc.cpp entities/Npc.h systems/AiSystem.cpp systems/AiSystem.h systems/CombatSystem.cpp systems/CombatSystem.h entities/Projectile.cpp entities/Projectile.h components/CollisionDamage.cpp components/CollisionDamage.h components/TimeToLive.cpp components/TimeToLive.h components/ViewRange.cpp components/ViewRange.h events/EntityCanSee.cpp events/EntityCanSee.h)

target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
