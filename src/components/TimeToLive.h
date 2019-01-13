//
// Created by armin on 13.01.19.
//

#ifndef GAME_TIMETOLIVE_H
#define GAME_TIMETOLIVE_H

#include <cstdint>
#include "Component.h"

namespace Components{
class TimeToLive:public Component {
public:
    TimeToLive(uint64_t pMsecs);
    int64_t mMsecs;
};
}


#endif //GAME_TIMETOLIVE_H
