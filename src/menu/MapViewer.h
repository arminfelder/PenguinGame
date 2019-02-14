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

#ifndef GAME_MAPVIEWER_H
#define GAME_MAPVIEWER_H

#include <memory>
#include <map>
#include <vector>
#include "MapRoom.h"

class MapViewer {
public:
    MapViewer();
    void render(SDL_Renderer* pRenderer);
    void close();

private:
    std::map<int, std::shared_ptr<MapRoom>> mapComponents;
    bool mRunning;
    void handleKeyEvent();

    SDL_Color mCurrentRoom;
    std::map<std::string,int> mMapMapping;
    std::vector<SDL_Rect> mDoorways;

};


#endif //GAME_MAPVIEWER_H
