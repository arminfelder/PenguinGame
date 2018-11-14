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
    int xPosition = this->position->getXPosition();
    int yPosition = this->position->getYPosition();
    this->fill = {xPosition, yPosition, this->dimension->getXDimension(), this->dimension->getYDimension()};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fill);
}

void entity::addOffset(int xOffset, int yOffset) {
    auto x = this->position->getXPosition() - xOffset;
    auto y = this->position->getYPosition() - yOffset;
    this->position->setPosition(x, y);
}
