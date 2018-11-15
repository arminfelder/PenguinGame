#ifndef GAME_MAP_H
#define GAME_MAP_H


#include "entityController.h"

class map {
public:
    explicit map(const char* mapName);
    class entityController* getEntityController();
    void draw(SDL_Renderer *renderer, int xOffset, int yOffset);
    void draw(SDL_Renderer* renderer);

private:
    int height;
    int length;
    class entityController* entityController;
};


#endif //GAME_MAP_H
