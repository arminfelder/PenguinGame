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
#include "HealthSystem.h"
#include "../managers/ComponentsManager.h"

Systems::HealthSystem::HealthSystem(SDL_Renderer *pRenderer, Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager),mRenderer(pRenderer) {
    std::function<void(std::shared_ptr<Events::Event>)> callback = [system = this](std::shared_ptr<Events::Event> pEvent)->void {
        auto event = static_cast<Events::HealthEvent*>(pEvent.get());
        auto healthComponent = Managers::ComponentsManager::getHealthComponent(event->entityId);
        int newHealth;
        int updatedHealth = healthComponent->getHealth()+event->healthDiff;
        if(updatedHealth <=0){
            //TODO: emit killed
            newHealth = 0;
        }else{
            newHealth = updatedHealth;
        }
        healthComponent->setHealth(newHealth);
        if(event->entityId == 1){
            //TODO: replace fixed id
            auto visualComponent = Managers::ComponentsManager::getVisualComponent(3);

            //TODO: memory leak, font loading etc...
            Uint8 gbColor;
            if(newHealth<= 100){
                gbColor = 255+(newHealth-100)*2.5;
            }

            SDL_Color textColor = {255, gbColor,gbColor, 255};
            SDL_Surface* healthMessage = TTF_RenderText_Blended(system->Sans.get(), std::to_string(newHealth).c_str(), textColor);
            auto healthMessageTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(system->mRenderer, healthMessage),SDL_DestroyTexture);
            SDL_FreeSurface(healthMessage);
            visualComponent->mTexture = healthMessageTexture;
        }

    };
    Sans = std::shared_ptr<TTF_Font>(TTF_OpenFont("./res/sans.ttf", 24), TTF_CloseFont);

    mEventsManager->regsiterEventHandler(Events::EventTypes::Health, callback );
}
