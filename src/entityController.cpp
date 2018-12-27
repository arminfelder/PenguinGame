#include <iostream>
#include "entityController.h"
#include "entity.h"
#include "player.h"

void entityController::createEntity(int health, class position *position, class dimension *dimension) {
    if (health == 10) {
        auto * entity = new class player(health, position, dimension);
    }
    auto * entity = new class entity(health, position, dimension);
    entities.push_back(entity);
}

void entityController::printEntities() {
    for (auto &entity : entities) {
        entity->print();
    }
}

//todo do this right using delete
void entityController::reset() {
    for (auto &entity : entities) {
        delete(entity);
    }
    entities.clear();
}


//legacy, don't use this anymore
void entityController::draw(SDL_Renderer *renderer) {
    for (class entity* entity : entities)
        entity->draw(renderer);
    SDL_RenderPresent(renderer);
}

std::list<entity *> entityController::getentities() {
    return entities;
}

entityController::~entityController() {
    entities.clear();
}
