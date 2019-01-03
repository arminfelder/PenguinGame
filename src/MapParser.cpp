//
// Created by armin on 30.12.18.
//

#include <fstream>
#include <SDL_ttf.h>
#include <iostream>
#include "MapParser.h"
#include "entities/MovementReset.h"
#include "entities/LadderEnd.h"
#include "entities/LadderBegin.h"
#include "entities/HealthIndicator.h"

SDL_Surface *MapParser::imageWall;
SDL_Texture *MapParser::textureWall;

SDL_Surface *MapParser::imagePlayer;
SDL_Texture *MapParser::texturePlayer;

SDL_Surface *MapParser::imageLadder;
SDL_Texture *MapParser::textureLadder;

SDL_Surface *MapParser::imageInvisible;
SDL_Texture *MapParser::textureInvisible;

using namespace Entities;


int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer ) {

    auto entityManager = pEngine->getEntityManager();

    imageWall = SDL_LoadBMP("./res/brick-wall.bmp");
    textureWall = SDL_CreateTextureFromSurface(pRenderer, imageWall);

    imagePlayer = SDL_LoadBMP("./res/hello.bmp");
    texturePlayer = SDL_CreateTextureFromSurface(pRenderer, imagePlayer);

    imageLadder = SDL_LoadBMP("./res/ladder.bmp");
    textureLadder = SDL_CreateTextureFromSurface(pRenderer, imageLadder);

    imageInvisible = SDL_LoadBMP("./res/invisible.bmp");
    textureInvisible = SDL_CreateTextureFromSurface(pRenderer, imageInvisible);

    //initial health text
    TTF_Font* Sans = TTF_OpenFont("./res/sans.ttf", 24);
    std::cout<< std::string(TTF_GetError())<<std::endl;
    SDL_Color White = {255, 255, 255, 255};
    SDL_Surface* healthMessage = TTF_RenderText_Blended(Sans, "100", White);
    SDL_Texture* healthMessageTexture = SDL_CreateTextureFromSurface(pRenderer, healthMessage);

    //health indicator
    int id = entityManager->createEntity<HealthIndicator>();
    Managers::ComponentsManager::createSpatialComponent(id, 20, 20);
    Managers::ComponentsManager::createVisualComponent(id,healthMessageTexture, 100,50);

    std::ifstream map;
    map.open(pMapfile);

    int line = 0;
    while(!map.eof()) {
        std::string currentLine;
        getline(map, currentLine);
        for (int i = 0; i < (int) currentLine.length(); i++) {

            int x = i*50;
            int y = line*50;
            //Defines entities given on the input from map file
            switch (currentLine[i]) {
                case '#': {
                    int id = entityManager->createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureWall, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case 'p': {
                    int id = 1;
                    Managers::ComponentsManager::createVisualComponent(id, texturePlayer, 48, 48);
                    Managers::ComponentsManager::createSpatialComponent(id, x+1, y+1);
                    Managers::ComponentsManager::createMoveAbleComponent(id,true,false,true,false );
                    Managers::ComponentsManager::createHealthComponent(id,100);
                    break;
                }
                case '|': {
                    int id = entityManager->createEntity<Ladder>();
                    Managers::ComponentsManager::createVisualComponent(id, textureLadder, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '=':{
                    int id = entityManager->createEntity<MovementReset>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '-':{
                    int id = entityManager->createEntity<LadderEnd>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case ':':{
                    int id = entityManager->createEntity<LadderBegin>();
                    Managers::ComponentsManager::createVisualComponent(id, textureLadder, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                default:
                    break;
            }
        }
        line++;



    }

    return 0;
}

void MapParser::cleanUp() {
    SDL_free(imageWall);
    SDL_free(textureWall);
    SDL_free(imagePlayer);
    SDL_free(texturePlayer);
    SDL_free(imageLadder);
    SDL_free(textureLadder);
    SDL_free(imageInvisible);
    SDL_free(textureInvisible);
}
