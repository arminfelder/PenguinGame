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
    uint64_t deltaTime = 0;
    int frames = 60;

    SDL_RegisterEvents(32769); //register Menu event
    SDL_RegisterEvents(32770); //register PauseMenu event
    SDL_RegisterEvents(32780); //register MenuSwitch event
    SDL_RegisterEvents(33332); //register Gameover event
    SDL_RegisterEvents(33333); //register New Game event
    SDL_Surface *surface = SDL_GetWindowSurface(mWindow);

    while (mRunning) {
        SDLEventLoop(&mRunning);
        //render one frame to get rid of the old menu. //todo make this better, like using a normal background image
        if (mRenderOnce) {
            mRenderOnce = false;
            drawFrame(last, now, frames);
        }
        if (mOpenMenu) {
            //todo find better solution to get rid of the already drawn ttfs without redrawing one frame after a menu change
            //Fill the surface white; todo work with other background.
//            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
//            SDL_UpdateWindowSurface(mWindow);
            mOpenMenu = false;
            mainMenu.get()->render(mRenderer);
            //SDLEventLoop(&mRunning);
            continue;

        } else if (mOpenPause) {
            mOpenPause = false;
            pauseMenu.get()->render(mRenderer);
            //SDLEventLoop(&mRunning);
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
    mWindow = SDL_CreateWindow("PenguinGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, 0);
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

void PenguinGame::SDLEventLoop(bool *mRunning) {
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {
        if (event.type == SDL_QUIT) {
            end();
            break;
        }
    }
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 32769, 32780)) {
        switch (event.type) {
            case 32769:
                mOpenMenu = true;
                break;
            case 32770:
                mOpenPause = true;
                break;
            case 32780:
                mRenderOnce = true;
                break;
        }
    }
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 33332, 33333)) {
        switch (event.type) {
            case 33332:
                mOpenGameOver = true;
                break;

            case 33333:
                newGame();
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

}

void PenguinGame::initGame() {
    auto entityManager = mGameEngine->getEntityManager();
    auto systemManager = mGameEngine->getSystemsManager();

    MapParser::createWorldFormMapTXT("./res/map.txt", mGameEngine, mRenderer, &collisionMask);
    systemManager->getCollisionSystem()->changeCollisionMask(&collisionMask);
    auto mapDimension = MapParser::getWorldDimension("./res/map.txt");
    systemManager->getCollisionSystem()->changeMapWidth(mapDimension.x);
}

void PenguinGame::initAudio() {
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    //SDL_LoadWAV("./res/04 All of Us.wav",&mWavSpec,&mWavBuffer,&mWavLength);
    //mAudiDdeviceId = SDL_OpenAudioDevice(NULL, 0, &mWavSpec, NULL, 0);
    //int success = SDL_QueueAudio(mAudiDdeviceId, mWavBuffer, mWavLength);
    //SDL_PauseAudioDevice(mAudiDdeviceId, 0);
}

void PenguinGame::newGame() {
    SDL_CloseAudioDevice(mAudiDdeviceId);
    SDL_FreeWAV(mWavBuffer);
    mGameEngine->~GameEngine();
    //mGameEngine = nullptr;
    SDL_DestroyRenderer(mRenderer);
    collisionMask.clear();

    initAudio();
    initEngine();
    initGame();
}

void PenguinGame::initMenus() {
    mainMenu = std::make_shared<Menu>();
    pauseMenu = std::make_shared<Menu>();
    gameOver = std::make_shared<Menu>();

    int position = mainMenu.get()->getMenuSize();
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "First entry", "red", position++, MenuEvents::NONE));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "New Game", "green", position++, MenuEvents::NEW_GAME));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Pause Menu", "green", position++, MenuEvents::PAUSE_MENU));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Exit Menu", "green", position++, MenuEvents::QUIT_MENU));
    mainMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Quit Game", "green", position++, MenuEvents::QUIT_GAME));

    position = pauseMenu.get()->getMenuSize();
    pauseMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Continue", "red", position++, MenuEvents::QUIT_MENU));
    pauseMenu.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Main Menu", "green", position++, MenuEvents::MAIN_MENU));

    position = gameOver.get()->getMenuSize();
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Game Over", "red", position++, MenuEvents::NONE));
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "New Game", "green", position++, MenuEvents::NEW_GAME));
    gameOver.get()->addMenuComponent(std::make_shared<MenuComponent>("Sans", "Quit Game", "green", position++, MenuEvents::QUIT_GAME));
}
