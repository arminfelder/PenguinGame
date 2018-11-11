#include "entity.h"
#include "position.h"
#include "dimension.h"

entity::entity(int health, class position* position, class dimension* dimension) {
    this->health = health;
    this->position = position;
    this->dimension = dimension;
}
