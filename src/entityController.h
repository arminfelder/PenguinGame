#ifndef GAME_ENTITYCONTROLLER_H
#define GAME_ENTITYCONTROLLER_H


#include <list>
#include "entity.h"

class entityController {
public:
    void createEntity(int health, class position* position, class dimension* dimension);
    void printEntities();
private:
    std::list<entity*> entities;
};


#endif //GAME_ENTITYCONTROLLER_H
