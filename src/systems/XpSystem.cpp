//
// Created by armin on 21.01.19.
//

#include "XpSystem.h"
#include "../events/EntityDied.h"
#include "../managers/ComponentsManager.h"

using namespace Systems;
XpSystem::XpSystem(SDL_Renderer *pRenderer,Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager),mRenderer(pRenderer) {
    auto callbackEntityDied = [system = this](const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::EntityDied*>(pEvent.get());
        //int entityId = event->mEntity;
        auto xp = Managers::ComponentsManager::getXp(1);
        if(xp){
            xp->mXp += event->mOrigHealth/10;

            auto visualComponent = Managers::ComponentsManager::getVisualComponent(4);

            if(visualComponent){
                int numberChars = 0;
                if(xp->mXp){
                    for(int i=xp->mXp; i>0; i /=10){
                        numberChars++;
                    }
                }else{
                    numberChars = 1;
                }

                int textLength = numberChars+4;

                auto xpString = std::string("XP: ")+std::to_string(xp->mXp);

                SDL_Color textColor = {255, 255, 255, 255};
                SDL_Surface *xpMessage = TTF_RenderText_Blended(system->Sans.get(),
                                                                    xpString.c_str(), textColor);
                auto xpMessageTexture = std::shared_ptr<SDL_Texture>(
                        SDL_CreateTextureFromSurface(system->mRenderer, xpMessage), SDL_DestroyTexture);
                SDL_FreeSurface(xpMessage);
                visualComponent->mTexture = xpMessageTexture;
                visualComponent->mImageRect.w = 24*textLength;
            }
        }
    };

    Sans = std::shared_ptr<TTF_Font>(TTF_OpenFont("./res/sans.ttf", 24), TTF_CloseFont);
    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityDied,callbackEntityDied);
}
