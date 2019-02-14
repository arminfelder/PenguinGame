/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <SDL_ttf.h>
#include <iostream>
#include "HealthSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/CollisionEvent.h"
#include "../events/EntityDied.h"


Systems::HealthSystem::HealthSystem(SDL_Renderer *pRenderer, Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager),mRenderer(pRenderer) {
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::HealthEvent*>(pEvent.get());
        auto healthComponent = Managers::ComponentsManager::getHealthComponent(event->entityId);
        if(healthComponent) {
            int newHealth;
            int updatedHealth = healthComponent->mHealth + event->healthDiff;
            if (updatedHealth <= 0) {
                //TODO: emit killed
                newHealth = 0;
                if (event->entityId != 1) {
                    auto spatial = Managers::ComponentsManager::getSpatialComponent(event->entityId);
                    auto inventory = Managers::ComponentsManager::getInventory(event->entityId);
                    if(spatial&&inventory) {
                        std::cout << "pos: " << spatial->mPositionX << " " << spatial->mPositionY << std::endl;
                        system->mEventsManager->addEvent(
                                std::make_shared<Events::EntityDied>(event->entityId, healthComponent->mOrigHealth,
                                                                     SDL_Point{spatial->mPositionX,
                                                                               spatial->mPositionY}, inventory));
                        Managers::ComponentsManager::removeComponentsOfEntity(event->entityId);
                        auto endsGame = Managers::ComponentsManager::getEndGame(event->entityId);
                        if (endsGame) {
                            SDL_Event sdl_event;
                            sdl_event.type = static_cast<Uint32>(33332);
                            SDL_PushEvent(&sdl_event);
                        }
                    }
                }
                else {//player dies -> game over //todo use our own event system
                    SDL_Event sdlEvent;
                    sdlEvent.type = 33332;
                    SDL_PushEvent(&sdlEvent);
                }
            } else {
                newHealth = updatedHealth;
            }

            healthComponent->mHealth =newHealth;
            if (event->entityId == 1) {
                //TODO: replace fixed id
                auto visualComponent = Managers::ComponentsManager::getVisualComponent(3);

                if (visualComponent) {
                    //TODO: memory leak, font loading etc...
                    Uint8 rColor;
                    Uint8 gColor;
                    Uint8 bColor;
                    if (newHealth <= 100) {
                        rColor = 255;
                        gColor = 255 + static_cast<Uint8>((newHealth - 100) * 2.5);
                        bColor = gColor;
                    } else {
                        rColor = 0;
                        gColor = 125;
                        bColor = 0;
                    }

                    int numberChars = 0;
                    if (newHealth) {

                        for (int i = newHealth; i > 0; i /= 10) {
                            numberChars++;
                            std::cout << newHealth << std::endl;
                            std::cout << i << std::endl;
                            std::cout << numberChars << std::endl;
                        }
                    } else {
                        numberChars = 1;
                    }

                    int textLength = numberChars + 4;

                    auto healthString = std::string("HP: ") + std::to_string(newHealth);

                    SDL_Color textColor = {rColor, gColor, bColor, 255};
                    SDL_Surface *healthMessage = TTF_RenderText_Blended(system->Sans.get(),
                                                                        healthString.c_str(), textColor);
                    auto healthMessageTexture = std::shared_ptr<SDL_Texture>(
                            SDL_CreateTextureFromSurface(system->mRenderer, healthMessage), SDL_DestroyTexture);
                    SDL_FreeSurface(healthMessage);
                    visualComponent->mTexture = healthMessageTexture;
                    visualComponent->mImageRect.w = 24 * textLength;
                }
            }
        }

    };
    Sans = std::shared_ptr<TTF_Font>(TTF_OpenFont("./res/sans.ttf", 24), TTF_CloseFont);

    auto collisionCallback = [system = this] (const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());
        if(event->mType == Events::collisionTypes::healthUp && event->mMovingEntity == 1){
            system->mEventsManager->addEvent(std::make_shared<Events::HealthEvent>(event->mMovingEntity,20));
            Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
            //TODO: remove Entity
        }else if(event->mType == Events::collisionTypes::npc){
            system->mEventsManager->addEvent(std::make_shared<Events::HealthEvent>(event->mMovingEntity,-30));
        }
    };


    mEventsManager->regsiterEventHandler(Events::EventTypes::Health, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, collisionCallback);
}

void Systems::HealthSystem::update(Uint64 pTime) {
    auto ttls = Managers::ComponentsManager::getTimeToLives();
    for(const auto &ttl: ttls){
        ttl.second->mMsecs -=pTime;
        if(ttl.second->mMsecs <=0){
            Managers::ComponentsManager::removeComponentsOfEntity(ttl.first);
        }
    }
}
