#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <SDL2/SDL.h>


class world {
private:
    SDL_Window* createWindow(int x, int y);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void cleanUp(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);
    void cleanUp(SDL_Window* window, SDL_Renderer* renderer);
    SDL_Surface* getImage(const char* name);
    void exampleLoop(SDL_Renderer* renderer, SDL_Texture* texture);
    ~world() = default;
public:
    void create(int x, int y);

};


#endif //GAME_WORLD_H
