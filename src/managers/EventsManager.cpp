//
// Created by armin on 28.12.18.
//

#include "EventsManager.h"

void Managers::EventsManager::dispatch(uint64_t pTimediff) {
    mTimediff = pTimediff;
    while(!mEventsQueue.empty()){
        auto event = mEventsQueue.front();
        mEventsQueue.pop();
        if(!mEventHandlers.empty()) {

            for (const auto &handler: mEventHandlers[event->getType()]){
                handler(event);
            }
        }
    }
}

void Managers::EventsManager::addEvent(const std::shared_ptr<Events::Event> &pEvent) {
    mEventsQueue.push(pEvent);
}

void Managers::EventsManager::regsiterEventHandler(Events::EventTypes pType, const std::function<void(const std::shared_ptr<Events::Event>& )> &pCallback) {
    auto pos = mEventHandlers.find(pType);
    if(pos == mEventHandlers.end()){
        mEventHandlers.insert({pType, {pCallback}});
    }else{
        mEventHandlers[pType].push_back(pCallback);
    }
}
