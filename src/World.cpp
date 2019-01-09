#include "world.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "TXTParser.h"
#include "map.h"


SDL_Window* world::createWindow(int x, int y) {
    SDL_Window *win = SDL_CreateWindow("Penguin Game", 100, 100, x, y, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return win;
}

SDL_Renderer *world::createRenderer(SDL_Window* window) {
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return ren;
}

//SDL_Surface *world::getImage(const char *name) {
//    std::string imagePath = getResourcePath() + name;
//    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
//    if (bmp == nullptr){
//        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//        return nullptr;
//    }
//    return bmp;
//}

void world::exampleLoop(SDL_Renderer *renderer, SDL_Texture *texture) {
    //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
        //First clear the renderer
        SDL_RenderClear(renderer);
        //Draw the texture
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        //Update the screen
        SDL_RenderPresent(renderer);
        //Take a quick break after all that hard work
        SDL_Delay(1000);
}

void world::create(int x, int y) {
    window = createWindow(x, y);
    renderer = createRenderer(window);
    //SDL_Surface* bmp = getImage("hello.bmp");

    //SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, bmp);
//
//    SDL_FreeSurface(bmp);
//    if (tex == nullptr){
//        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//        return;
//    }
//
//
//
//    SDL_Event e;
//    auto quit = false;
//    while(!quit) {
//        exampleLoop(renderer, tex);
//
//        //part for eventHandler
//        while (SDL_PollEvent(&e)){
//            if (e.type == SDL_QUIT){
//                quit = true;
//            }
//            if (e.key.keysym.sym == SDLK_x)
//                quit = true;
//        }
//    }
//    quit = false;
//    while (!quit) {
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//        SDL_Rect fillRect = { x / 4, y / 4, y / 2, x / 2 };
//        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderFillRect( renderer, &fillRect );
//
//        //Draw blue horizontal line
//        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
//        SDL_RenderDrawLine( renderer, 0, y / 2, x, y / 2 );
//
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);
//        //part for eventHandler
//        while (SDL_PollEvent(&e)){
//            if (e.type == SDL_QUIT){
//                quit = true;
//            }
//            if (e.key.keysym.sym == SDLK_x)
//                quit = true;
//        }
//    }

    auto * map = new class map("map.txt");

    //render blank
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    auto quit = false;
    while(!quit) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        map->draw(renderer);
        SDL_Delay(17); //roughly 60 fps
        SDL_RenderPresent(renderer);
        SDL_Event e;


        //part for inputHandler/eventHandler
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.key.keysym.sym == SDLK_x || e.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
            if (e.key.keysym.sym == SDLK_d && e.key.type == SDL_KEYDOWN)
                map->movePlayer(renderer, mult/2, 0);
            if (e.key.keysym.sym == SDLK_a && e.key.type == SDL_KEYDOWN)
                map->movePlayer(renderer, -mult/2, 0);
            if (e.key.keysym.sym == SDLK_w && e.key.type == SDL_KEYDOWN)
                map->movePlayer(renderer, 0, mult/2);
            if (e.key.keysym.sym == SDLK_s && e.key.type == SDL_KEYDOWN)
                map->movePlayer(renderer, 0, -mult/2);
        }
    }
}


void world::cleanUp(SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
}

world::~world() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}