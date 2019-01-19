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

#include <utility>

#include <memory>
#include <iostream>
#include "MenuComponent.h"



const SDL_Color MenuComponent::matchColor(std::string color) {
    SDL_Color sdl_color = {0, 0, 0};
    if (color == "grey")
        sdl_color = {62, 62, 62};
    else if (color == "red")
        sdl_color = {232,23,23};
    else if (color == "green")
        sdl_color = {23,232,23};
    else if (color == "blue")
        sdl_color = {23,23,232};

    return sdl_color;
}

MenuComponent::MenuComponent(std::string font, std::string text, std::string color, int position, MenuEvents::MenuEventType menuEventType) {
    this->position = position;
    this->color = std::move(color);
    this->text = std::move(text);
    this->font = std::move(font);
    this->menuEvent = menuEventType;
}

std::shared_ptr<SDL_Surface> MenuComponent::getSurface() {
    std::shared_ptr<TTF_Font> Sans(TTF_OpenFont("./res/sans.ttf", 24),TTF_CloseFont);
    auto textColor = matchColor(color);
    std::shared_ptr<SDL_Surface> menuComponent(TTF_RenderText_Blended(Sans.get(), text.c_str(), textColor), SDL_FreeSurface);
    return menuComponent;
}

int MenuComponent::getPosition() {
    return position;
}

void MenuComponent::updateColor(std::string color) {
    this->color = std::move(color);
}

MenuEvents::MenuEventType MenuComponent::getMenuEventType() {
    return this->menuEvent;
}

bool MenuComponent::isItem() {
    if ((this->itemType == static_cast<Components::Inventory::ItemTypes>(-1))) //no item
        return false;
    else
        return true;
}
