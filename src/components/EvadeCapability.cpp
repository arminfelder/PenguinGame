//
// Created by armin on 25.01.19.
//

#include "EvadeCapability.h"

using namespace Components;
EvadeCapability::EvadeCapability(int pEvadeProbability):mChance(pEvadeProbability) {

}

std::string EvadeCapability::serialize() {
    return "EvadeCapability;" + std::to_string(mChance);
}

bool EvadeCapability::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "EvadeCapability" && splittedStrings.size() == 2) {
        mChance = std::stoi(splittedStrings[1]);
        return true;
    }
    return false;
}