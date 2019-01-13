//
// Created by armin on 12.01.19.
//

#ifndef GAME_PATH_H
#define GAME_PATH_H

#include <vector>
#include <SDL_rect.h>
#include "Component.h"

namespace Components {
    class Path:public Component {
    public:
        Path(const std::vector<SDL_Point> &pPath, int pStepsPerSecond ,bool repeat = true, bool running=true);
        std::vector<SDL_Point> mPath;
        int mCurrPos = 0;
        bool mRepeat;
        bool mRunning;
        int mStepsPerFrame;
        int mTimeSinceLastStep = 0;
        int mXmovedCurStep = 0;
        int mYmovedCurStep = 0;
    };
}


#endif //GAME_PATH_H
