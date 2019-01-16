#ifndef GAME_MENUCOMPONENT_H
#define GAME_MENUCOMPONENT_H


#include <string>
#include <SDL_pixels.h>
#include <SDL_ttf.h>

class MenuComponent {

public:
    MenuComponent(std::string font, std::string text, std::string color, int position);
    std::shared_ptr<SDL_Surface> getSurface();
    int getPosition();

    void updateColor(std::string color);

private:
    const SDL_Color matchColor(std::string color);
    std::string font;
    std::string text;
    std::string color;
    int position;
};


#endif //GAME_MENUCOMPONENT_H
