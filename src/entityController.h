#ifndef GAME_ENTITYCONTROLLER_H
#define GAME_ENTITYCONTROLLER_H


#include <list>
#include <SDL_render.h>
#include "entity.h"

class entityController {
public:
    void createEntity(int health, class position* position, class dimension* dimension);
    void printEntities();
    void reset();
    void draw(SDL_Renderer* renderer);
private:
    std::list<entity*> entities;
};


#endif //GAME_ENTITYCONTROLLER_H
