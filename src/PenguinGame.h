#ifndef GAME_PENGUINGAME_H
#define GAME_PENGUINGAME_H


#include <SDL_video.h>
#include "GameEngine.h"

class PenguinGame {

public:
    PenguinGame();
    int run();
    void initSDL();
    void initEngine();

    void initGame();

    void end();
    ~PenguinGame();
private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    bool mRunning = false;
    GameEngine *mGameEngine = nullptr;
};


#endif //GAME_PENGUINGAME_H
