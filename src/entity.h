#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include <SDL_render.h>
#include "position.h"
#include "dimension.h"

class entity {
public:
    entity(int health, position* position, dimension* dimension);
    void print();
    void draw(SDL_Renderer* renderer);
    void addOffset(int xOffset, int yOffset);
    bool isPlayer();
private:
    int health;
    bool player = false;
    class position* position;
    class dimension* dimension;
    SDL_Rect fill;

};


#endif //GAME_ENTITY_H
