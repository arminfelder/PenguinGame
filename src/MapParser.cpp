//
// Created by armin on 30.12.18.
//

#include <fstream>
#include "MapParser.h"

int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer ) {

    auto entityManager = pEngine->getEntityManager();

    SDL_Surface *imageWall = SDL_LoadBMP("./res/brick-wall.bmp");
    SDL_Texture *textureWall = SDL_CreateTextureFromSurface(pRenderer, imageWall);

    SDL_Surface *imagePlayer = SDL_LoadBMP("./res/hello.bmp");
    SDL_Texture *texturePlayer = SDL_CreateTextureFromSurface(pRenderer, imagePlayer);


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
                    int id = entityManager->createEntity();
                    Managers::ComponentsManager::createVisualComponent(id, textureWall, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    break;
                }
                case 'p': {
                    int id = 1;
                    Managers::ComponentsManager::createVisualComponent(id, texturePlayer, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createMoveAbleComponent(id,true,false,true,false );
                    break;
                }
                case '|':
                    break;
                default:
                    break;
            }
        }
        line++;
    }

    return 0;
}
