#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <SDL2/SDL.h>

extern int mult;

class world {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* getImage(const char* name);

    SDL_Window* createWindow(int x, int y);
    SDL_Renderer* createRenderer(SDL_Window* window);

    void cleanUp(SDL_Texture* texture);
    void exampleLoop(SDL_Renderer* renderer, SDL_Texture* texture);
public:
    void create(int x, int y);
    ~world();
};


#endif //GAME_WORLD_H
