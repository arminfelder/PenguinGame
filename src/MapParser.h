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
    struct mapDimension {
        int x, y;
    };
public:
    static int createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask);
    static mapDimension getWorldDimension(const std::string &pMapfile);
    static void printCollisionMask(std::vector<bool> collisionMask, int xDimension);
    static std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>> generateTexturesMap(const std::map<std::string,std::list<std::string>> &pBmps,const std::string &pString, SDL_Renderer *pRenderer);
};


#endif //GAME_MAPPARSER_H
