#include "map.h"
#include "TXTParser.h"

map::map(const char* mapName) {
    entityController = new class entityController();
    std::vector<int> boundaries = TXTParser::parseMap(mapName, entityController);
    this->height= boundaries[0];
    this->length= boundaries[1];

    //Demo for actual working of TXTParser
    entityController->printEntities();
//    entityController->reset();
}

class entityController *map::getEntityController() {
    return this->entityController;
}

void map::draw(SDL_Renderer *renderer) {
    map::draw(renderer, 0, 0);
}

void map::draw(SDL_Renderer *renderer, int xOffset, int yOffset) {
    std::list<entity *> entities = entityController->getentities();
    for (class entity* entity : entities) {
        if (xOffset != 0 || yOffset != 0)
            entity->addOffset(xOffset, yOffset);
        entity->draw(renderer);
    }
}


map::~map() {
}

void map::movePlayer(SDL_Renderer *renderer, int xOffset, int yOffset) {
    std::list<entity *> entities = entityController->getentities();
    for (class entity* entity : entities) {
        if ((xOffset != 0 || yOffset != 0) && entity->isPlayer()) {
            entity->addOffset(xOffset, yOffset);

        }
        entity->draw(renderer);
    }
}

