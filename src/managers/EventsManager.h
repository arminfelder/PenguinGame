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


#ifndef GAME_EVENTSMAMAGER_H
#define GAME_EVENTSMAMAGER_H

#include <queue>
#include <map>
#include <unordered_map>
#include <list>
#include <functional>
#include <memory>
#include <SDL_quit.h>
#include "../events/Event.h"

namespace Managers {

    class EventsManager {

    public:
        void dispatch(Uint64 pTimediff);
        void addEvent(const std::shared_ptr<Events::Event> &pEvent);
        void regsiterEventHandler(Events::EventTypes,const std::function<void(const std::shared_ptr<Events::Event>& )> &pEvent);
        Uint64 mTimediff;
        ~EventsManager();
    private:
        std::queue<std::shared_ptr<Events::Event> > mEventsQueue;
        std::unordered_map<Events::EventTypes , std::list<std::function<void(const std::shared_ptr<Events::Event> &pEvent )> > > mEventHandlers;
    };

}


#endif //GAME_EVENTSMAMAGER_H
