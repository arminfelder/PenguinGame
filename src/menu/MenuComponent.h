#ifndef GAME_MENUCOMPONENT_H
#define GAME_MENUCOMPONENT_H


#include <string>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include "MenuEvents.h"

class MenuComponent {

public:
    MenuComponent(std::string font, std::string text, std::string color, int position, MenuEvents::MenuEventType);
    std::shared_ptr<SDL_Surface> getSurface();
    int getPosition();
    void updateColor(std::string color);
    MenuEvents::MenuEventType getMenuEventType();

private:
    const SDL_Color matchColor(std::string color);
    std::string font;
    std::string text;
    std::string color;
    int position;
    MenuEvents::MenuEventType menuEvent;
};


#endif //GAME_MENUCOMPONENT_H
