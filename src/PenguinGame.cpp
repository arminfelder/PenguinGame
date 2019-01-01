#include "PenguinGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "World.h"
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
    while (mRunning){
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = ((now - last)*1000 / SDL_GetPerformanceFrequency() );
        SDL_Event event;
        SDL_PumpEvents();
        while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)){
            if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                mRunning = false;
            }

        }
        mGameEngine->update(deltaTime);
        SDL_Delay( 1000/frames );

    }

    return 0;
}

void PenguinGame::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    mWindow = SDL_CreateWindow("PenguinGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
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

    MapParser::createWorldFormMapTXT("./res/map.txt", mGameEngine, mRenderer);

}

void PenguinGame::initAudio() {
    SDL_LoadWAV("./res/04 All of Us.wav",&mWavSpec,&mWavBuffer,&mWavLength);
    mAudiDdeviceId = SDL_OpenAudioDevice(NULL, 0, &mWavSpec, NULL, 0);
    int success = SDL_QueueAudio(mAudiDdeviceId, mWavBuffer, mWavLength);
    SDL_PauseAudioDevice(mAudiDdeviceId, 0);
}
