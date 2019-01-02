//
// Created by armin on 30.12.18.
//

#include <fstream>
#include "MapParser.h"
#include "entities/MovementReset.h"
#include "entities/LadderEnd.h"
#include "entities/LadderBegin.h"


using namespace Entities;


int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer ) {

    auto entityManager = pEngine->getEntityManager();

    SDL_Surface *imageWall = SDL_LoadBMP("./res/brick-wall.bmp");
    SDL_Texture *textureWall = SDL_CreateTextureFromSurface(pRenderer, imageWall);

    SDL_Surface *imagePlayer = SDL_LoadBMP("./res/hello.bmp");
    SDL_Texture *texturePlayer = SDL_CreateTextureFromSurface(pRenderer, imagePlayer);

    SDL_Surface *imageLadder = SDL_LoadBMP("./res/ladder.bmp");
    SDL_Texture *textureLadder = SDL_CreateTextureFromSurface(pRenderer, imageLadder);

    SDL_Surface *imageInvisible = SDL_LoadBMP("./res/invisible.bmp");
    SDL_Texture *textureInvisible = SDL_CreateTextureFromSurface(pRenderer, imageInvisible);


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
