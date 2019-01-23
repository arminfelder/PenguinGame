//
// Created by armin on 21.01.19.
//

#ifndef GAME_XP_H
#define GAME_XP_H

#include <zconf.h>
#include <string>
#include <vector>
#include "Component.h"

namespace Components {
    class Xp: public Component {
    public:
        Xp();
        std::string serialize();
        bool load(std::vector<std::string> splittedStrings);
        uint mXp = 0;
    };
}


#endif //GAME_XP_H
