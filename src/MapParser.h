//
// Created by armin on 30.12.18.
//

#ifndef GAME_MAPPARSER_H
#define GAME_MAPPARSER_H

#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "GameEngine.h"
#include "entity.h"
#include "entities/Wall.h"
#include "entities/Ladder.h"

class MapParser {
public:
    static int createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer);

};


#endif //GAME_MAPPARSER_H
