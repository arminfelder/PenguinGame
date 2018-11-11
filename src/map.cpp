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
    this->entityController->draw(renderer);
}
