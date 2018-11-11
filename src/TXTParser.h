#ifndef GAME_TXTPARSER_H
#define GAME_TXTPARSER_H


#include <fstream>
#include "entityController.h"

class TXTParser {
public:
    void static parseMap(const char* mapName);

private:
    unsigned long static getMapHeight(std::ifstream& map);
    unsigned long static getMapLength(std::ifstream& map);
    void static readMap(std::ifstream& map, entityController* entityController);
};


#endif //GAME_TXTPARSER_H
