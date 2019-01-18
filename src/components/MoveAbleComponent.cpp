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

#include "MoveAbleComponent.h"

Components::MoveAbleComponent::MoveAbleComponent() {

}

Components::MoveAbleComponent::MoveAbleComponent(bool pRight, bool pDown, bool pLeft, bool pTop):canMoveRight(pRight),canMoveDown(pDown),canMoveLeft(pLeft),canMoveUp(pTop) {

}

std::string Components::MoveAbleComponent::serialize() {
    std::string serialize = "MoveAble;" + std::to_string(this->canMoveLeft) + ";" + std::to_string(this->canMoveRight) + ";" + std::to_string(this->canMoveDown) + ";" + std::to_string(this->canMoveUp);
    return serialize;
}

void Components::MoveAbleComponent::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "MoveAble") {
        canMoveLeft = static_cast<bool>(std::stoi(splittedStrings[1]));
        canMoveRight = static_cast<bool>(std::stoi(splittedStrings[2]));
        canMoveDown = static_cast<bool>(std::stoi(splittedStrings[3]));
        canMoveUp = static_cast<bool>(std::stoi(splittedStrings[4]));

    }

}
