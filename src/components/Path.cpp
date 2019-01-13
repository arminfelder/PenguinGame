//
// Created by armin on 12.01.19.
//

#include "Path.h"

Components::Path::Path(const std::vector<SDL_Point> &pPath, int pStepsPerSecond , bool repeat, bool running):mPath(pPath),mRepeat(repeat),mRunning(running),mStepsPerFrame(pStepsPerSecond) {

}
