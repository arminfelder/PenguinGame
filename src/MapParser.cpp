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
#include "entities/Npc.h"
#include "entities/Key.h"
#include "entities/Door.h"
#include "entities/TeleporterEntrance.h"
#include "entities/TeleporterTarget.h"

using namespace Entities;
using namespace std;

int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer, std::vector<bool> *collisionMask ) {

    auto entityManager = pEngine->getEntityManager();
    auto mapDimension = getWorldDimension(pMapfile);


    std::shared_ptr<SDL_Surface> imageWall(SDL_LoadBMP("./res/brick-wall.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureWall(SDL_CreateTextureFromSurface(pRenderer, imageWall.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageStoneWall(SDL_LoadBMP("./res/stone-wall-2477715_640.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureStoneWall(SDL_CreateTextureFromSurface(pRenderer, imageStoneWall.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageStoneWall2(SDL_LoadBMP("./res/00.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureStoneWall2(SDL_CreateTextureFromSurface(pRenderer, imageStoneWall2.get()), SDL_DestroyTexture);

    map<string, list<string>> playerBmps;
    playerBmps.insert({"walk",{"./res/tux/big/walk-0.bmp","./res/tux/big/walk-1.bmp","./res/tux/big/walk-2.bmp","./res/tux/big/walk-3.bmp","./res/tux/big/walk-4.bmp","./res/tux/big/walk-5.bmp","./res/tux/big/walk-6.bmp","./res/tux/big/walk-7.bmp"}});

    auto playerMap = generateTexturesMap(playerBmps,"./res/tux/big/idle-0.bmp",pRenderer);


    std::shared_ptr<SDL_Surface> imageHeart(SDL_LoadBMP("./res/heart_4.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureHeart(SDL_CreateTextureFromSurface(pRenderer, imageHeart.get()), SDL_DestroyTexture);

    map<string, list<string>> doorBmps;
    doorBmps.insert({"open",{"./res/door_open.bmp"}});
    doorBmps.insert({"closed",{"./res/door_closed.bmp"}});
    auto doorMap = generateTexturesMap(doorBmps,"./res/door_closed.bmp", pRenderer);

    std::shared_ptr<SDL_Surface> imageKey(SDL_LoadBMP("./res/secret_key.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureKey(SDL_CreateTextureFromSurface(pRenderer, imageKey.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageDoorClosed(SDL_LoadBMP("./res/door_closed.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureDoorClosed(SDL_CreateTextureFromSurface(pRenderer, imageDoorClosed.get()), SDL_DestroyTexture);


    std::shared_ptr<SDL_Surface> imageMonster1(SDL_LoadBMP("./res/monster/MonsterPack_008/depixelizer_1453475703255.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureMonster1(SDL_CreateTextureFromSurface(pRenderer, imageMonster1.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageTeleporterEntry(SDL_LoadBMP("./res/teleporter_entry.bmp"),SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureTeleporterEntry(SDL_CreateTextureFromSurface(pRenderer, imageTeleporterEntry.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageTeleporterTarget(SDL_LoadBMP("./res/teleporter_target.bmp"),SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureTeleporterTarget(SDL_CreateTextureFromSurface(pRenderer, imageTeleporterTarget.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageMonster2(SDL_LoadBMP("./res/monster/MonsterPack_008/depixelizer_1453475724139.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureMonster2(SDL_CreateTextureFromSurface(pRenderer, imageMonster2.get()), SDL_DestroyTexture);


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
        int teleporterTarget;
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
                case '&':{
                    int id = Managers::EntityManager::createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureStoneWall2, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    collisionMask->pop_back();
                    collisionMask->push_back(true);
                    break;
                }
                case 'T':{
                    int id = Managers::EntityManager::createEntity<TeleporterEntrance>();
                    Managers::ComponentsManager::createVisualComponent(id, textureTeleporterEntry, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    //useless
                    teleporterTarget = id;
                    break;
                }
                case 't':{
                    int id = Managers::EntityManager::createEntity<TeleporterTarget>();
                    Managers::ComponentsManager::createVisualComponent(id, textureTeleporterTarget, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createTeleportTarget(id, teleporterTarget);
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
                case 'k':{
                    int id = Managers::EntityManager::createEntity<Key>();
                    Managers::ComponentsManager::createVisualComponent(id, textureKey, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case 'd':{
                    int id = Managers::EntityManager::createEntity<Door>();
                    Managers::ComponentsManager::createVisualComponent(id, doorMap, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    Managers::ComponentsManager::createUseable(id, {Components::Inventory::ItemTypes::keyArea2});
                    break;
                }
                case 'p': {
                    int id = 1;
                    Managers::ComponentsManager::createVisualComponent(id, playerMap, 48, 48);
                    Managers::ComponentsManager::createSpatialComponent(id, x+1, y+1);
                    Managers::ComponentsManager::createMoveAbleComponent(id,true,false,true,false );
                    Managers::ComponentsManager::createHealthComponent(id,100);
                    Managers::ComponentsManager::createMomentumComponent(id);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    Managers::ComponentsManager::createInventory(id);
                    Managers::ComponentsManager::createCanCollect(id, {Components::Inventory::ItemTypes::keyArea2});
                    break;
                }
                case 'h': {
                    int id = Managers::EntityManager::createEntity<HealthItem>();
                    Managers::ComponentsManager::createVisualComponent(id, textureHeart, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case 'm': {
                    int id = Managers::EntityManager::createEntity<Npc>();
                    Managers::ComponentsManager::createVisualComponent(id, textureMonster1, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    Managers::ComponentsManager::createHealthComponent(id,50);
                    Managers::ComponentsManager::createPathComponent(id,std::vector<SDL_Point>({SDL_Point{100,0},SDL_Point{-100,0}}),1,true,true);
                    Managers::ComponentsManager::createViewRange(id, 400,0);
                    break;
                }
                case 'M':{
                    int id = Managers::EntityManager::createEntity<Npc>();
                    Managers::ComponentsManager::createVisualComponent(id, textureMonster2, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    Managers::ComponentsManager::createHealthComponent(id,80);
                    Managers::ComponentsManager::createPathComponent(id,std::vector<SDL_Point>({SDL_Point{-150,0},SDL_Point{150,0}}),1,true,true);
                    Managers::ComponentsManager::createViewRange(id, 600,0);
                    break;
                }
                case 'K':{
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


    printCollisionMask(*collisionMask, 102);
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

void MapParser::printCollisionMask(std::vector<bool> collisionMask, int xDimension) {
    int counter = 0;
    std::ostream &out = std::cout;
    for (bool element : collisionMask) {
        if (++counter == 102) {
            out << std::endl << std::endl;
            counter = 0;
        }
        out << element << " ";
    }
}
