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

#include "VisitedMaps.h"

bool Components::VisitedMaps::addMap(const std::string mapName) {
        for (const auto &map : mMapList) {
            if (map == mapName)
                return false;
        }
    mMapList.push_back(mapName);
    return true;
}

std::string Components::VisitedMaps::serialize() {
    std::string serialize = "VisitedMaps";
    for (const auto &map : mMapList) {
        serialize += ";" + map;
    }
    return serialize;
}

bool Components::VisitedMaps::load(std::vector<std::string> splittedStrings) {
    auto size = splittedStrings.size();
    if (splittedStrings[0] == "VisitedMaps") {
        for (unsigned long i = 1; i < size; i++)
            addMap(splittedStrings[i]);
    }
    return true;
}

std::vector<std::string> &Components::VisitedMaps::getVisitedMaps() {
    return mMapList;
}
