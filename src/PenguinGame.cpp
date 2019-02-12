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

#include "PenguinGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <filesystem>
#include "MapParser.h"
#include "menu/Menu.h"


int PenguinGame::run() {

    initSDL();
    initAudio();
    initEngine();
    initGame();
    initMenus();
    auto now = SDL_GetPerformanceCounter();
    uint64_t last = now;
    int frames = 60;

    SDL_RegisterEvents(32769); //register Menu event
    SDL_RegisterEvents(32770); //register PauseMenu event
    SDL_RegisterEvents(32780); //register MenuSwitch event
    SDL_RegisterEvents(32791); //register LoadMap1 event
    SDL_RegisterEvents(32792); //register LoadMap2 event
    SDL_RegisterEvents(32793); //register LoadMap3 event
    SDL_RegisterEvents(33332); //register Gameover event
    SDL_RegisterEvents(33333); //register New Game event
    SDL_RegisterEvents(33334); //register Load Game event
//    SDL_Surface *surface = SDL_GetWindowSurface(mWindow);

    while (mRunning) {
        SDLEventLoop();
        //render one frame to get rid of the old menu. //todo make this better, like using a normal background image
        if (mRenderOnce) {
            mRenderOnce = false;
            drawFrame(last, now, frames);
        }
        if (mOpenMenu) {
            //todo find better solution to get rid of the already drawn ttfs without redrawing one frame after a menu change
//            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
//            SDL_UpdateWindowSurface(mWindow);
            mOpenMenu = false;
            mainMenu.get()->render(mRenderer);
            continue;

        } else if (mOpenPause) {
            mOpenPause = false;
            pauseMenu.get()->render(mRenderer);
            continue;

        } else if (mOpenGameOver) {
            mOpenGameOver = false;
            mOpenPause = false;
            mOpenMenu = false;
            mRenderOnce = false;
            gameOver.get()->render(mRenderer);
            continue;

        } else {
            drawFrame(last, now, frames);
        }
    }

    return 0;
}

void PenguinGame::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    mWindow = SDL_CreateWindow("PenguinGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!mWindow) {
        SDL_Log("failed to create window: %s", SDL_GetError());
    }
    mRunning = true;
}

void PenguinGame::drawFrame(uint64_t &last, uint64_t &now, int frames) {
    last = now;
    now = SDL_GetPerformanceCounter();
    uint64_t deltaTime = ((now - last) * 1000 / SDL_GetPerformanceFrequency());
    mGameEngine->update(deltaTime);
    SDL_Delay(static_cast<Uint32> (1000 / frames));
}

void PenguinGame::SDLEventLoop() {
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {
        if (event.type == SDL_QUIT) {
            end();
            break;
        }
    }
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 32769, 32793)) {
        switch (event.type) {
            case 32769:
                mOpenMenu = true;
                break;
            case 32770:
                pauseMenu->updateInventory();
                mOpenPause = true;
                break;
            case 32780:
                mRenderOnce = true;
                break;
            case 32791:
                newGame("./res/map.txt");
                break;
            case 32792:
                newGame("./res/map2.txt");
                break;
            case 32793:
                newGame("./res/map3.txt");
                break;
            default:
                break;
        }
    }
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 33332, 33335)) {
        switch (event.type) {
            case 33332:
                mOpenGameOver = true;
                break;

            case 33333:
                newGame();
                break;

            case 33335: {//continue game on another map -> save data in intermediate file
                auto idptr = reinterpret_cast<int*>(event.user.data1);
                auto id = *idptr;
                auto collideAbles = Managers::ComponentsManager::getCollideAble();
                int jumperCounter = 0;
                int playerPosition = 0;
                std::string map;
                for (const auto &collideAble : collideAbles) {
                    auto entity = Managers::EntityManager::getEntity(collideAble.first);
                    auto type = entity->getType();
                    if (type == Entities::entityTypes::mapChanger) {
                        //compare if id matches with the one from event
                        if (collideAble.first == id) { //found jump
                            map = getMapFileNameFromJumper(jumperCounter);
                            playerPosition = getPlayerPositionFromJumper(jumperCounter);
                            break;
                        } else
                            jumperCounter++;
                    }
                }

                delete idptr;
                loadMapPreservingUserStats(map, playerPosition);
                break;
            }
            case 33334: { //load game data including correct map
                std::string filename = Managers::ComponentsManager::getMapName().get()->getMapName();
                newGame(filename);
                std::ifstream in("save.txt");
                Managers::ComponentsManager::loadUserComponents(in);
                in.close();
                mGameEngine->getEventManager()->addEvent(std::make_shared<Events::HealthEvent>(1, 0));
                auto xpSystem = mGameEngine->getSystemsManager()->getXpSystem();
                xpSystem->drawXp();
                break;
            }
            default:
                break;
        }
    }
}

void PenguinGame::initEngine() {
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    mGameEngine = new GameEngine(mWindow, mRenderer);
}

PenguinGame::~PenguinGame() {
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
    }
    SDL_CloseAudioDevice(mAudiDdeviceId);
    SDL_FreeWAV(mWavBuffer);
    SDL_Quit();
}

void PenguinGame::end() {
    mRunning = false;
}

PenguinGame::PenguinGame() {
    std::srand(std::time(nullptr));
}

void PenguinGame::loadMap(const std::string &mMapFile, int playerPosition) {
    auto systemManager = mGameEngine->getSystemsManager();

    MapParser::createWorldFromMapTXT(mMapFile, mGameEngine, mRenderer, &collisionMask, playerPosition);
    systemManager->getCollisionSystem()->changeCollisionMask(&collisionMask);
    auto mapDimension = MapParser::getWorldDimension(mMapFile);
    systemManager->getCollisionSystem()->changeMapWidth(mapDimension.x);
    Managers::ComponentsManager::createMapName(mMapFile);
}

void PenguinGame::loadMap(const std::string &mMapFile) {
    loadMap(mMapFile, 0);
}

void PenguinGame::loadMapPreservingUserStats(const std::string &mMapFile, int playerPosition) {
    std::string filename = "tmp.txt";
    //save intermediate data into file
    std::ofstream out(filename);
    Managers::ComponentsManager::prepareNextMap(out);
    out.close();

    //load map and load the saved user data
    newGame(mMapFile, playerPosition);
    std::ifstream in(filename);
    if (!Managers::ComponentsManager::loadUserComponents(in)) //check if loading the map would work
        Menu::sendSDLEvent(33333); //create new game if loading went wrong
    in.close();

    //update health to display correctly
    mGameEngine->getEventManager()->addEvent(std::make_shared<Events::HealthEvent>(1, 0));
    auto xpSystem = mGameEngine->getSystemsManager()->getXpSystem();
    xpSystem->drawXp();
    //mGameEngine->getEventManager()->addEvent(std::make_shared<Events::XPEvent>(1,0));
    remove(filename.c_str());
}

void PenguinGame::loadMapPreservingUserStats(const std::string &mMapFile) {
    loadMapPreservingUserStats(mMapFile, 0);
}

void PenguinGame::initGame() {
    std::string map = "./res/maps/area1/map.txt";
    loadMap(map);
}

void PenguinGame::initAudio() {
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    //SDL_LoadWAV("./res/04 All of Us.wav",&mWavSpec,&mWavBuffer,&mWavLength);
    //mAudiDdeviceId = SDL_OpenAudioDevice(NULL, 0, &mWavSpec, NULL, 0);
    //int success = SDL_QueueAudio(mAudiDdeviceId, mWavBuffer, mWavLength);
    //SDL_PauseAudioDevice(mAudiDdeviceId, 0);
}

void PenguinGame::newGame(const std::string &mMapFile, int playerPosition) {
    SDL_CloseAudioDevice(mAudiDdeviceId);
    SDL_FreeWAV(mWavBuffer);
    mGameEngine->~GameEngine();
    //mGameEngine = nullptr;
    SDL_DestroyRenderer(mRenderer);
    collisionMask.clear();

    initAudio();
    initEngine();
    loadMap(mMapFile, playerPosition);
}

void PenguinGame::newGame(const std::string &mMapFile) {
    newGame(mMapFile, 0);
}

void PenguinGame::newGame() {
    newGame((const std::string &) "./res/maps/area1/map.txt");
}

void PenguinGame::initMenus() {
    mainMenu = std::make_shared<Menu>();
    pauseMenu = std::make_shared<Menu>();
    gameOver = std::make_shared<Menu>();

    int position = mainMenu.get()->getMenuSize();
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "New Game", "red", position++, MenuEvents::NEW_GAME));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Save Game", "green", position++, MenuEvents::SAVE_GAME));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Load Game", "green", position++, MenuEvents::LOAD_GAME));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Pause Menu", "green", position++, MenuEvents::PAUSE_MENU));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Exit Menu", "green", position++, MenuEvents::QUIT_MENU));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Quit Game", "green", position++, MenuEvents::QUIT_GAME));

    position = pauseMenu.get()->getMenuSize();
    pauseMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Continue", "red", position++, MenuEvents::QUIT_MENU));
    pauseMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Main Menu", "green", position++, MenuEvents::MAIN_MENU));

    position = gameOver.get()->getMenuSize();
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Game Over", "red", position++, MenuEvents::NONE));
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "New Game", "green", position++, MenuEvents::NEW_GAME));
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Load Game", "green", position++, MenuEvents::LOAD_GAME));
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Quit Game", "green", position++, MenuEvents::QUIT_GAME));
}

std::string PenguinGame::getMapFileNameFromJumper(int jumperID) {
    std::string map = "./res/maps/";
    int mapID = getMapIDFromJumper(jumperID);

    if (mapID != -1) {
        auto mapLine = getConnectionMapLine(mapID);
        if (mapLine.size() > 1)
            map += mapLine[0];
    }

    if (map == "./res/maps/") //map somehow not found -> set default
        map += "area1/map.txt";
    return map;
}

int PenguinGame::getPlayerPositionFromJumper(int jumperID) {
    std::ifstream connectionFile("./res/maps/connection.txt");
    std::string line;
    std::string map = "./res/maps/";
    int playerPosition = 0;

    while (std::getline(connectionFile, line)) {
        std::vector<std::string> splittedStrings = Managers::ComponentsManager::splitString(line, ';');

        if (("./res/maps/" + splittedStrings[0]) == Managers::ComponentsManager::getMapName().get()->getMapName()) {
            if (static_cast<int>(splittedStrings.size()) > (jumperID + 1) * 2)
                playerPosition = std::stoi(splittedStrings[jumperID * 2 + 2]);
            break;
        }
    }
    connectionFile.close();
    return playerPosition;
}

int PenguinGame::getMapIDFromJumper(int jumperID) {
    std::ifstream connectionFile("./res/maps/connection.txt");
    std::string line;
    std::string map = "./res/maps/";
    int mapID = -1;

    while (std::getline(connectionFile, line)) {
        std::vector<std::string> splittedStrings = Managers::ComponentsManager::splitString(line, ';');

        if (("./res/maps/" + splittedStrings[0]) == Managers::ComponentsManager::getMapName().get()->getMapName()) {
            if (static_cast<int>(splittedStrings.size()) > (jumperID + 1) * 2)
                mapID = std::stoi(splittedStrings[jumperID * 2 + 1]);
            break;
        }
    }
    connectionFile.close();
    return mapID;
}

std::vector<std::string> PenguinGame::getConnectionMapLine(int mapID) {
    if (mapID != -1) {
        std::ifstream connectionFile("./res/maps/connection.txt");
        int counter = 1; //used to select correct map line
        std::string line;
        while (std::getline(connectionFile, line)) {
            if (counter == mapID) {
                std::vector<std::string> splittedStrings = Managers::ComponentsManager::splitString(line, ';');
                return splittedStrings;
            } else
                counter++;
        }

        connectionFile.close();
    }
    return {""};
}
