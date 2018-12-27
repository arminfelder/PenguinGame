#include "Map.h"
#include "TXTParser.h"

Map::Map(const std::string &mapName) {
    entityController = new EntityController();
    std::vector<int> boundaries = TXTParser::parseMap(mapName, entityController);
    this->height= boundaries[0];
    this->length= boundaries[1];

    //Demo for actual working of TXTParser
    entityController->printEntities();
//    EntityController->reset();
}

class EntityController *Map::getEntityController() {
    return this->entityController;
}

void Map::draw(SDL_Renderer *renderer) {
    Map::draw(renderer, 0, 0);
}

void Map::draw(SDL_Renderer *renderer, int xOffset, int yOffset) {
    std::list<Entity *> entities = entityController->getentities();
    for (class Entity* entity : entities) {
        if (xOffset != 0 || xOffset != 0)
            entity->addOffset(xOffset, yOffset);
        entity->draw(renderer);
    }
}

