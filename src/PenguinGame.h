#ifndef GAME_PENGUINGAME_H
#define GAME_PENGUINGAME_H


#include <SDL_video.h>
#include <SDL_audio.h>
#include "GameEngine.h"

class PenguinGame {

public:
    PenguinGame();
    int run();
    void initSDL();
    void initEngine();
    void initAudio();

    void initGame();

    void end();
    ~PenguinGame();
private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    bool mRunning = false;
    GameEngine *mGameEngine = nullptr;


    //audio
    SDL_AudioSpec mWavSpec;
    Uint32 mWavLength;
    Uint8 *mWavBuffer = nullptr;
    SDL_AudioDeviceID mAudiDdeviceId;
};


#endif //GAME_PENGUINGAME_H
