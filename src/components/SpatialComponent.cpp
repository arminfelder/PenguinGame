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

#include <string>
#include <iostream>
#include "SpatialComponent.h"

Components::SpatialComponent::SpatialComponent(int pPositionX, int pPositionY, bool pMoveWithMap) {
    mPositionX = pPositionX;
    mPositionY = pPositionY;
    //set previous to starting values to prevent physics problems if an immediate collision happens
    mPrevPositionX = pPositionX;
    mPrevPositionY = pPositionY;
    moveWithMap = pMoveWithMap;
}

std::string Components::SpatialComponent::serialize() {
    std::string serialized = "SpatialComponent;" + std::to_string(this->mPositionX) + ";" + std::to_string(this->mPositionY) + ";" +
                             std::to_string(this->mPrevPositionX) + ";" + std::to_string(this->mPrevPositionY);
    return serialized;
}

bool Components::SpatialComponent::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "SpatialComponent" && splittedStrings.size() >= 5) {
        mPositionX = std::stoi(splittedStrings[1]);
        mPositionY = std::stoi(splittedStrings[2]);
        mPrevPositionX = std::stoi(splittedStrings[3]);
        mPrevPositionY = std::stoi(splittedStrings[4]);
    }
    else
        return false;
    return true;
}
