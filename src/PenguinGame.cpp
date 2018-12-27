#include "PenguinGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "World.h"


int PenguinGame::run() {

    initSDL();
    initEngine();
    initGame();
    while (mRunning){
        SDL_Event event;
        SDL_PumpEvents();
        while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)){
            if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                mRunning = false;
            }

            mGameEngine->update(1);
        }
    }

    return 0;
}

void PenguinGame::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    mWindow = SDL_CreateWindow("PenguinGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if(!mWindow){
        SDL_Log("failed to create window: %s", SDL_GetError());
    }
    mRunning = true;
}

void PenguinGame::initEngine() {
    mRenderer = SDL_CreateRenderer(mWindow, -1,0);
    mGameEngine = new GameEngine(mWindow, mRenderer);
}

PenguinGame::~PenguinGame() {
    if(mWindow){
        SDL_DestroyWindow(mWindow);
    }
    SDL_Quit();
}

void PenguinGame::end() {
    mRunning = false;
}

PenguinGame::PenguinGame() {

}

void PenguinGame::initGame() {
    auto entityManager = mGameEngine->getEntityManager();
    int id = entityManager->createEntity();

    SDL_Surface *image = SDL_LoadBMP("./res/hello.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, image);

    Managers::ComponentsManager::createVisualComponent(id,texture,50,50);
    Managers::ComponentsManager::createSpatialComponent(id, 30,30);
}
