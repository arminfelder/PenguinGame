//
// Created by armin on 30.12.18.
//

#ifndef GAME_MAPPARSER_H
#define GAME_MAPPARSER_H

#include <string>
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
};
#endif //GAME_MAPPARSER_H
