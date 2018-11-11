#include <iostream>
#include "entity.h"
#include "position.h"
#include "dimension.h"

entity::entity(int health, class position* position, class dimension* dimension) {
    this->health = health;
    this->position = position;
    this->dimension = dimension;
}

void entity::print() {
    std::cout << "Health: " << this->health << ", Position: " << this->position->getXPosition() << ", " << this->position->getYPosition() << std::endl;
}

void entity::draw(SDL_Renderer *renderer) {
    SDL_Rect fill = {this->position->getXPosition(), this->position->getYPosition(), this->dimension->getXDimension(), this->dimension->getYDimension()};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fill);
}
