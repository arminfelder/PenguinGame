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

#ifndef GAME_PENGUINGAME_H
#define GAME_PENGUINGAME_H


#include <SDL_video.h>
#include <SDL_audio.h>
#include "GameEngine.h"
#include "menu/Menu.h"

class PenguinGame {

public:
    PenguinGame();
    int run();
    void initSDL();
    void initEngine();
    void initAudio();
    void SDLEventLoop(bool* mRunning);
    void initGame();
    void initMenus();

    void newGame();
    void end();
    ~PenguinGame();
private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    bool mRunning = false;
    GameEngine *mGameEngine = nullptr;
    std::vector<bool> collisionMask;

    //audio
    SDL_AudioSpec mWavSpec;
    Uint32 mWavLength;
    Uint8 *mWavBuffer = nullptr;
    SDL_AudioDeviceID mAudiDdeviceId;

    //Menu
    bool mOpenMenu = false;
    bool mOpenPause = false;
    bool mOpenGameOver = false;
    std::shared_ptr<Menu> mainMenu;
    std::shared_ptr<Menu> pauseMenu;
    std::shared_ptr<Menu> gameOver;

};


#endif //GAME_PENGUINGAME_H
