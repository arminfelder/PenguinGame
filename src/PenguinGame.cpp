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


int PenguinGame::run() {

    initSDL();
    initAudio();
    initEngine();
    initGame();
    auto now = SDL_GetPerformanceCounter();
    uint64_t last = now;
    uint64_t deltaTime = 0;
    int frames = 60;

    SDL_RegisterEvents(32769); //register menu event
    SDL_Surface *surface = SDL_GetWindowSurface(mWindow);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    while (mRunning) {
        if (mMenu) {
            //Fill the surface white
            SDLEventLoop(&mMenu, &mRunning);
            SDL_UpdateWindowSurface(mWindow);
            SDL_Delay(static_cast<Uint32> (1000 / frames));
            //mMenu = false;
        } else {
            last = now;
            now = SDL_GetPerformanceCounter();
            deltaTime = ((now - last) * 1000 / SDL_GetPerformanceFrequency());
            SDLEventLoop(&mMenu, &mRunning);
            mGameEngine->update(deltaTime);
            SDL_Delay(static_cast<Uint32> (1000 / frames));

        }
    }

    return 0;
}

void PenguinGame::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    mWindow = SDL_CreateWindow("PenguinGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, 0);
    if(!mWindow){
        SDL_Log("failed to create window: %s", SDL_GetError());
    }
    mRunning = true;
}

void PenguinGame::SDLEventLoop(bool* mMenu, bool* mRunning) {
    SDL_Event event;
    SDL_PumpEvents();
    if (*mMenu) {
        while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_KEYDOWN)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                *mMenu = !*mMenu;
                break;
            }
        }
    }

    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {
        if (event.type == SDL_QUIT) {
            *mRunning = false;
            break;
        }
    }
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 32769, 32769)) {
        if (event.type == 32769) { //open menu
            *mMenu = !*mMenu;
        }
    }

}

void PenguinGame::initEngine() {
    mRenderer = SDL_CreateRenderer(mWindow, -1,0);
    mGameEngine = new GameEngine(mWindow, mRenderer);
}

PenguinGame::~PenguinGame() {
    if(mWindow){
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
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    //SDL_LoadWAV("./res/04 All of Us.wav",&mWavSpec,&mWavBuffer,&mWavLength);
    //mAudiDdeviceId = SDL_OpenAudioDevice(NULL, 0, &mWavSpec, NULL, 0);
    //int success = SDL_QueueAudio(mAudiDdeviceId, mWavBuffer, mWavLength);
    //SDL_PauseAudioDevice(mAudiDdeviceId, 0);
}
