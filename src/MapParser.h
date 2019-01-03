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
    static int createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer);
    static void cleanUp();

private:
    static SDL_Surface *imageWall;
    static SDL_Texture *textureWall;

    static SDL_Surface *imagePlayer;
    static SDL_Texture *texturePlayer;

    static SDL_Surface *imageLadder;
    static SDL_Texture *textureLadder;

    static SDL_Surface *imageInvisible;
    static SDL_Texture *textureInvisible;

    static SDL_Surface* healthMessage;
    static SDL_Texture* healthMessageTexture;
};


#endif //GAME_MAPPARSER_H
