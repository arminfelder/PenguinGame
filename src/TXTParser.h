#ifndef GAME_TXTPARSER_H
#define GAME_TXTPARSER_H


#include <fstream>
#include <vector>
#include "entityController.h"
extern int mult;

class TXTParser {
public:
    class std::vector<int> static parseMap(const char* mapName, class entityController* entityController);

private:
    unsigned long static getMapHeight(std::ifstream& map);
    unsigned long static getMapLength(std::ifstream& map);
    void static readMap(std::ifstream& map, entityController* entityController);
};


#endif //GAME_TXTPARSER_H
