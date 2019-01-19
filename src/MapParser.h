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

#ifndef GAME_MAPPARSER_H
#define GAME_MAPPARSER_H

#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "GameEngine.h"
#include "entities/Wall.h"
#include "entities/Ladder.h"

class MapParser {
public:
    struct mapDimension {
        int x, y;
    };
public:
    static int createWorldFromMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask);
    static mapDimension getWorldDimension(const std::string &pMapfile);
    static void printCollisionMask(std::vector<bool> collisionMask, int xDimension);
    static std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>>
    generateTexturesMap(const std::map<std::string, std::list<std::string>> &pBmps, const std::string &pString, SDL_Renderer *pRenderer);
    static void destroyMap(GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask, SDL_Window* pWindow);
    static void loadMap(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask, SDL_Window* pWindow);
};


#endif //GAME_MAPPARSER_H
