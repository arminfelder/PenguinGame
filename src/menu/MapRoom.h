//
// Created by armin on 14.02.19.
//

#ifndef GAME_MAPROOM_H
#define GAME_MAPROOM_H


#include <SDL_rect.h>
#include <string>
#include <SDL_render.h>

class MapRoom {
public:
    MapRoom(SDL_Rect pRect, const std::string &pColor);

    std::shared_ptr<SDL_Surface> getSurface();

    const SDL_Color matchColor(std::string color);
    SDL_Rect mRect;
    std::string color;


};


#endif //GAME_MAPROOM_H
