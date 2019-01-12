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

#include <fstream>
#include <iostream>
#include "MapParser.h"
#include "entities/MovementReset.h"
#include "entities/LadderEnd.h"
#include "entities/LadderBegin.h"
#include "entities/HealthIndicator.h"
#include "entities/HealthItem.h"

using namespace Entities;
using namespace std;

int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask ) {

    auto entityManager = pEngine->getEntityManager();
    auto mapDimension = getWorldDimension(pMapfile);

    std::shared_ptr<SDL_Surface> imageWall(SDL_LoadBMP("./res/brick-wall.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureWall(SDL_CreateTextureFromSurface(pRenderer, imageWall.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageStoneWall(SDL_LoadBMP("./res/stone-wall-2477715_640.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureStoneWall(SDL_CreateTextureFromSurface(pRenderer, imageStoneWall.get()), SDL_DestroyTexture);

    map<string, list<string>> playerBmps;
    playerBmps.insert({"walk",{"./res/tux/big/walk-0.bmp","./res/tux/big/walk-1.bmp","./res/tux/big/walk-2.bmp","./res/tux/big/walk-3.bmp","./res/tux/big/walk-4.bmp","./res/tux/big/walk-5.bmp","./res/tux/big/walk-6.bmp","./res/tux/big/walk-7.bmp"}});

    auto playerMap = generateTexturesMap(playerBmps,"./res/tux/big/idle-0.bmp",pRenderer);


    std::shared_ptr<SDL_Surface> imageHeart(SDL_LoadBMP("./res/heart_4.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureHeart(SDL_CreateTextureFromSurface(pRenderer, imageHeart.get()), SDL_DestroyTexture);



    std::shared_ptr<SDL_Surface> imageLadder(SDL_LoadBMP("./res/ladder.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureLadder(SDL_CreateTextureFromSurface(pRenderer, imageLadder.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageInvisible(SDL_LoadBMP("./res/invisible.bmp"),SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureInvisible(SDL_CreateTextureFromSurface(pRenderer, imageInvisible.get()), SDL_DestroyTexture);


    //initial health text
    std::shared_ptr<TTF_Font> Sans(TTF_OpenFont("./res/sans.ttf", 24),TTF_CloseFont);
    SDL_Color White = {255, 255, 255, 255};
    std::shared_ptr<SDL_Surface> healthMessage(TTF_RenderText_Blended(Sans.get(), "100", White), SDL_FreeSurface);
    auto healthMessageTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, healthMessage.get()), SDL_DestroyTexture);

    //health indicator
    int id = Managers::EntityManager::createEntity<HealthIndicator>();
    Managers::ComponentsManager::createSpatialComponent(id, 20, 20, false);
    Managers::ComponentsManager::createVisualComponent(id,healthMessageTexture, 100,50);

    std::ifstream map;
    map.open(pMapfile);

    int line = 0;
    while(!map.eof()) {
        std::string currentLine;
        getline(map, currentLine);
        for (int i = 0; i < (int) currentLine.length(); i++) {
            collisionMask->push_back(false);
            int x = i*50;
            int y = line*50;
            //Defines entities given on the input from map file
            switch (currentLine[i]) {
                case '#': {
                    int id = Managers::EntityManager::createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureWall, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    collisionMask->pop_back();
                    collisionMask->push_back(true);
                    break;
                }
                case '+':{
                    int id = Managers::EntityManager::createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureStoneWall, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    collisionMask->pop_back();
                    collisionMask->push_back(true);
                    break;
                }
                case 'i':{
                    int id = Managers::EntityManager::createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    collisionMask->pop_back();
                    collisionMask->push_back(true);
                    break;
                }
                case 'p': {
                    int id = 1;
                    Managers::ComponentsManager::createVisualComponent(id, playerMap, 48, 48);
                    Managers::ComponentsManager::createSpatialComponent(id, x+1, y+1);
                    Managers::ComponentsManager::createMoveAbleComponent(id,true,false,true,false );
                    Managers::ComponentsManager::createHealthComponent(id,100);
                    Managers::ComponentsManager::createMomentumComponent(id);
                    break;
                }
                case 'h': {
                    int id = Managers::EntityManager::createEntity<HealthItem>();
                    Managers::ComponentsManager::createVisualComponent(id, textureHeart, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '|': {
                    int id = Managers::EntityManager::createEntity<Ladder>();
                    Managers::ComponentsManager::createVisualComponent(id, textureLadder, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '=':{
                    int id = Managers::EntityManager::createEntity<MovementReset>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '-':{
                    int id = Managers::EntityManager::createEntity<LadderEnd>();
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
            //fill up line for negative mask
            if (i+1 == static_cast<int>( currentLine.size())) { //reached end of line
                for (int j = static_cast<int>(currentLine.size()); j < mapDimension.x; j++)
                    collisionMask->push_back(false);
            }
        }
        line++;



    }
    return 0;
}


MapParser::mapDimension MapParser::getWorldDimension(const std::string &pMapfile) {
    std::ifstream map;
    map.open(pMapfile);
    int line = 0;
    int maxLineLenght = 0;
    while (!map.eof()) {
        line++;
        std::string currentLine;
        getline(map, currentLine);
        if (static_cast<int> (currentLine.length()) > maxLineLenght)
            maxLineLenght = static_cast<int>(currentLine.length());
    }
    MapParser::mapDimension mapDimension{};
    mapDimension.x = maxLineLenght;
    mapDimension.y = line;
    return mapDimension;
}

std::shared_ptr<map<string, vector<shared_ptr<SDL_Texture>>>>
MapParser::generateTexturesMap(const map<string, list<string>> &pMap,const std::string &pDefault , SDL_Renderer *pRenderer) {

    auto returnMap = make_shared<map<string, vector<shared_ptr<SDL_Texture>>>>(map<string,vector<shared_ptr<SDL_Texture>>>());
    for(const auto &entry: pMap ){
        returnMap->insert({entry.first,vector<shared_ptr<SDL_Texture>>()});
        for(const auto &bmp: entry.second){
            std::shared_ptr<SDL_Surface> image(SDL_LoadBMP(bmp.c_str()), SDL_FreeSurface) ;
            std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(pRenderer, image.get()), SDL_DestroyTexture);
            returnMap.get()->at(entry.first).push_back(texture);
        }
    }
    std::shared_ptr<SDL_Surface> image(SDL_LoadBMP(pDefault.c_str()), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(pRenderer, image.get()), SDL_DestroyTexture);
    returnMap->insert({"default",{texture}});

    return returnMap;
}

