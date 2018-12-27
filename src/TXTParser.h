#ifndef GAME_TXTPARSER_H
#define GAME_TXTPARSER_H


#include <fstream>
#include <vector>
#include "EntityController.h"

class TXTParser {
public:
    static std::vector<int> parseMap(const std::string &mapName, EntityController* entityController);

private:
    unsigned long static getMapHeight(std::ifstream& map);
    unsigned long static getMapLength(std::ifstream& map);
    void static readMap(std::ifstream& map, EntityController* entityController);
};


#endif //GAME_TXTPARSER_H
