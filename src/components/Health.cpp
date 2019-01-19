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


#include <sstream>
#include <cstring>
#include <vector>
#include "Health.h"

using namespace Components;

void Health::operator++() {
    mHealth++;
}

void Health::operator--() {
    mHealth--;
}

int Health::getHealth() {
    return mHealth;
}

void Health::setHealth(int health) {
    mHealth = health;
}

Health::Health(int pHealth) : mHealth(pHealth) {

}

std::string Health::serialize() {
    std::string serialized = "Health;" + std::to_string(this->mHealth);
    return serialized;
}

bool Health::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "Health" && splittedStrings.size() >= 2) {
        setHealth(std::stoi(splittedStrings[1]));
        return true;
    }
    return false;
}