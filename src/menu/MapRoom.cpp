//
// Created by armin on 14.02.19.
//

#include <memory>
#include "MapRoom.h"

MapRoom::MapRoom(SDL_Rect pRect,const std::string &pColor):mRect(pRect),color(pColor) {

}

const SDL_Color MapRoom::matchColor(std::string color) {
    SDL_Color sdl_color = {0, 0, 0, 0};
    if (color == "grey")
        sdl_color = {62, 62, 62, 255};
    else if (color == "red")
        sdl_color = {232,23,23, 255};
    else if (color == "green")
        sdl_color = {23,232,23, 128};
    else if (color == "blue")
        sdl_color = {23,23,255, 255};

    return sdl_color;
}

std::shared_ptr<SDL_Surface> MapRoom::getSurface() {
    return  std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, mRect.h, mRect.h ,32,0,0,0,0), SDL_FreeSurface);;
}
