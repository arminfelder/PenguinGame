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

#include "Momentum.h"

Components::Momentum::Momentum() {

}

std::string Components::Momentum::serialize() {
    std::string serialize = "Momentum;" + std::to_string(this->speedX) + ";" + std::to_string(this->speedY);
    return serialize;
}

bool Components::Momentum::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "Momentum" && splittedStrings.size() >= 3) {
        speedX = std::stoi(splittedStrings[1]);
        speedY = std::stoi(splittedStrings[2]);
        return true;
    }
    return false;
}
