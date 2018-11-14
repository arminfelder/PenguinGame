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
private:
    int health;
    class position* position;
    class dimension* dimension;
};


#endif //GAME_ENTITY_H
