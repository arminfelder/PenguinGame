#include "World.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "TXTParser.h"
#include "Map.h"


SDL_Window* World::createWindow(int x, int y) {
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, x, y, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return win;
}

SDL_Renderer *World::createRenderer(SDL_Window* window) {
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return ren;
}

//SDL_Surface *World::getImage(const char *name) {
//    std::string imagePath = getResourcePath() + name;
//    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
//    if (bmp == nullptr){
//        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//        return nullptr;
//    }
//    return bmp;
//}

void World::exampleLoop(SDL_Renderer *renderer, SDL_Texture *texture) {
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

void World::create(int x, int y) {

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

    auto * map = new Map("Map.txt");


    //render blank
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);

    auto quit = false;
    while(!quit) {
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        map->draw(mRenderer);
        SDL_Delay(17); //roughly 60 fps
        SDL_RenderPresent(mRenderer);
        SDL_Event e;


        //part for eventHandler
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.key.keysym.sym == SDLK_x)
                quit = true;
            if (e.key.keysym.sym == SDLK_d && e.key.type == SDL_KEYDOWN)
                map->draw(mRenderer, 5, 0);
            if (e.key.keysym.sym == SDLK_a && e.key.type == SDL_KEYDOWN)
                map->draw(mRenderer, -5, 0);
        }
    }
    cleanUp(mWindow, mRenderer);
    SDL_Quit();
}


void World::cleanUp(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void World::cleanUp(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

World::~World() {
    if(mRenderer) {
        SDL_DestroyRenderer(mRenderer);
    }
    if(mWindow) {
        SDL_DestroyWindow(mWindow);
    }

    SDL_Quit();
}

World::World(int x, int y) {
    mWindow = createWindow(x, y);
    mRenderer = createRenderer(mWindow);
}

void World::init() {

}
