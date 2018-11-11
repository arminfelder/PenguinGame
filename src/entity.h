#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include "position.h"
#include "dimension.h"

class entity {
public:
    entity(int health, position* position, dimension* dimension);
    void print();
private:
    int health;
    class position* position;
    class dimension* dimension;
};


#endif //GAME_ENTITY_H
