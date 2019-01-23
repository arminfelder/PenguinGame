//
// Created by armin on 21.01.19.
//

#include "Xp.h"

using namespace Components;
Xp::Xp() {

}

bool Xp::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "XP") {
        mXp = static_cast<uint>(std::stoi(splittedStrings[1]));
        return true;
    }
    return false;
}

std::string Xp::serialize() {
    std::string serialized = "XP;"+std::to_string(mXp);
    return serialized;
}

