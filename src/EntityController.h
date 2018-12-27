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
    std::list<entity*> getentities();
private:
    std::list<entity*> entities;
    ~entityController();
};


#endif //GAME_ENTITYCONTROLLER_H
