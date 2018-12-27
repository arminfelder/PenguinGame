#ifndef GAME_ENTITYCONTROLLER_H
#define GAME_ENTITYCONTROLLER_H


#include <list>
#include <SDL_render.h>
#include "entities/Entity.h"

class EntityController {
public:
    void createEntity(int health, class position* position, class Dimension* dimension);
    void printEntities();
    void reset();
    void draw(SDL_Renderer* renderer);
    std::list<Entities::Entity*> getentities();
private:
    std::list<Entities::Entity*> entities;
    int mEntityIdCount = 0;
};


#endif //GAME_ENTITYCONTROLLER_H
