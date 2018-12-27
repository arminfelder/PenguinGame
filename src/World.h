#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <SDL2/SDL.h>


class World {
private:
    SDL_Window* createWindow(int x, int y);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void cleanUp(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);
    void cleanUp(SDL_Window* window, SDL_Renderer* renderer);
    SDL_Surface* getImage(const char* name);
    void exampleLoop(SDL_Renderer* renderer, SDL_Texture* texture);

    void init();
public:
    World() = default;
    World(int x, int y);
    void create(int x, int y);
    ~World();

private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer*  mRenderer = nullptr;

};


#endif //GAME_WORLD_H
