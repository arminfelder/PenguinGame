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

add_executable(game main.cpp
	    PenguinGame.cpp
        entities/Entity.cpp
        entities/Player.cpp
        entities/Wall.cpp
        entities/Ladder.cpp
        entities/MovementReset.cpp
        entities/LadderEnd.cpp
        entities/LadderBegin.cpp
        entities/HealthIndicator.cpp
        entities/HealthItem.cpp
        entities/Npc.cpp
        entities/Projectile.cpp
	    entities/Key.cpp
	    entities/Door.cpp
        entities/TeleporterEntrance.cpp
        entities/TeleporterTarget.cpp
        GameEngine.cpp
        systems/RenderSystem.cpp
        systems/InputSystem.cpp
        systems/HealthSystem.cpp
        systems/PositionSystem.cpp
        systems/CollisionSystem.cpp
        systems/PhysicsSystem.cpp
        systems/AudioSystem.cpp
        systems/TextureSystem.cpp
        systems/TriggerSystem.cpp
        systems/AiSystem.cpp
        systems/CombatSystem.cpp
	    systems/TriggerSystem.cpp
	    systems/InventorySystem.cpp
        managers/EntityManager.cpp
        managers/SystemsManager.cpp
        managers/ComponentsManager.cpp
        managers/EventsManager.cpp
        menu/MenuComponent.cpp
        menu/Menu.cpp
        menu/MenuEvents.cpp
        components/VisualComponent.cpp
        components/SpatialComponent.cpp
        components/Health.cpp
        components/MoveAbleComponent.cpp
        components/CollideAble.cpp
        components/CameraOffset.cpp
        components/Momentum.cpp
        components/Gravity.cpp
        components/Path.cpp
        components/CollisionDamage.cpp
        components/TimeToLive.cpp
        components/ViewRange.cpp
	    components/Inventory.cpp
	    components/CanCollect.cpp
	    components/UseAbel.cpp
        components/TeleportTarget.cpp
		components/MapName.cpp
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
        events/EntityCanSee.cpp
        events/PlayerDies.cpp
        events/TriggerActivated.cpp
        MapParser.cpp
		)

target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
