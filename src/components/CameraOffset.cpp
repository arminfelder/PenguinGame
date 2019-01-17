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

#include "CameraOffset.h"

using namespace Components;
CameraOffset::CameraOffset(int pXOffset, int pYOffset): xOffset (pXOffset), yOffset (pYOffset)  {}

int CameraOffset::getXOffset() const {
    return xOffset;
}

void CameraOffset::setXOffset(int xOffset) {
    CameraOffset::xOffset = xOffset;
}

int CameraOffset::getYOffset() const {
    return yOffset;
}

void CameraOffset::setYOffset(int yOffset) {
    CameraOffset::yOffset = yOffset;
}

std::string CameraOffset::serialize() {
    std::string serialize = "CameraOffset;" + std::to_string(xOffset) + ";" + std::to_string(yOffset);
    return serialize;
}

void CameraOffset::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "CameraOffset") {
        xOffset = std::stoi(splittedStrings[1]);
        yOffset = std::stoi(splittedStrings[2]);
    }

}
