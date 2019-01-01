//
// Created by armin on 28.12.18.
//

#ifndef GAME_EVENTSMAMAGER_H
#define GAME_EVENTSMAMAGER_H

#include <queue>
#include <map>
#include <unordered_map>
#include <list>
#include <functional>
#include <memory>
#include "../events/Event.h"

namespace Managers {

    class EventsManager {

    public:
        void dispatch(uint64_t pTimediff);
        void addEvent(const std::shared_ptr<Events::Event> &pEvent);
        void regsiterEventHandler(Events::EventTypes,const std::function<void(const std::shared_ptr<Events::Event>& )> &pEvent);
        uint64_t mTimediff;
    private:
        std::queue<std::shared_ptr<Events::Event> > mEventsQueue;
        std::unordered_map<Events::EventTypes , std::list<std::function<void(const std::shared_ptr<Events::Event> &pEvent )> > > mEventHandlers;
    };

}


#endif //GAME_EVENTSMAMAGER_H
