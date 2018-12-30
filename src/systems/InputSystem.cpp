//
// Created by armin on 27.12.18.
//

#include <SDL_events.h>
#include "InputSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyUpEvent.h"

using namespace Systems;
void InputSystem::update() {
    SDL_Event event;

    while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_MOUSEWHEEL)){
        switch (event.type){

            case SDL_KEYDOWN: {
                mEventsManager->addEvent(std::make_shared<Events::KeyPressedEvent>(event.key.keysym));
                break;
            }
            case SDL_KEYUP: {
                mEventsManager->addEvent(std::make_shared<Events::KeyUpEvent>(event.key.keysym));
                break;
            }
        }
    }
}

InputSystem::InputSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
}
