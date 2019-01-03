//
// Created by armin on 22.12.18.
//

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
