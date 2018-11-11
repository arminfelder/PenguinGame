#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include "position.h"
#include "dimension.h"

class entity {
public:
    entity(int health, position* position, dimension* dimension);
private:
    int health;
    class position* position;
    class dimension* dimension;
};


#endif //GAME_ENTITY_H
