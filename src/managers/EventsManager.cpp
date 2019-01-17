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

Managers::EventsManager::~EventsManager() {
    //clear queue
    std::queue<std::shared_ptr<Events::Event> > empty;
    std::swap(mEventsQueue, empty);

    mEventHandlers.clear();
}
