#include <iostream>
#include "EntityController.h"

using namespace Entities;
void EntityController::createEntity(int health, class position *position, class Dimension *dimension) {
    auto * entity = new Entity(mEntityIdCount++);
    entities.push_back(entity);
}

void EntityController::printEntities() {
    for (auto &entity : entities) {
        entity->print();
    }
}

//todo do this right using delete
void EntityController::reset() {
    for (auto &entity : entities) {
        delete(entity);
    }
    entities.clear();
}


//legacy, don't use this anymore
void EntityController::draw(SDL_Renderer *renderer) {
    for (class Entity* entity : entities)
        entity->draw(renderer);
    SDL_RenderPresent(renderer);
}

std::list<Entity *> EntityController::getentities() {
    return entities;
}
