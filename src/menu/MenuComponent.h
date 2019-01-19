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

#ifndef GAME_MENUCOMPONENT_H
#define GAME_MENUCOMPONENT_H


#include <string>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include "MenuEvents.h"
#include "../components/Inventory.h"

class MenuComponent {

public:
    MenuComponent(std::string font, std::string text, std::string color, int position, MenuEvents::MenuEventType);
    MenuComponent(std::string font, std::string text, std::string color, int position, MenuEvents::MenuEventType menuEventType, Components::Inventory::ItemTypes itemType) : MenuComponent(font, text, color, position, menuEventType) {this->itemType = itemType;};
    std::shared_ptr<SDL_Surface> getSurface();
    int getPosition();
    void updateColor(std::string color);
    MenuEvents::MenuEventType getMenuEventType();
    bool isItem();
    Components::Inventory::ItemTypes getItemType();

private:
    const SDL_Color matchColor(std::string color);
    std::string font;
    std::string text;
    std::string color;
    int position;
    Components::Inventory::ItemTypes itemType = static_cast<Components::Inventory::ItemTypes>(-1);
    MenuEvents::MenuEventType menuEvent;
};


#endif //GAME_MENUCOMPONENT_H
