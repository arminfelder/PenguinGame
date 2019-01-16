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

MenuComponent::MenuComponent(std::string font, std::string text, std::string color, int position, MenuEvents::MenuEventType menuType) {
    this->position = position;
    this->color = std::move(color);
    this->text = std::move(text);
    this->font = std::move(font);
    this->menuEvent = menuType;
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
