#include "TXTParser.h"
#include "entityController.h"
//#include "res_path.h"
#include <string>
#include <fstream>
#include <iostream>


void TXTParser::parseMap(const char *mapName) {
//    std::string location = getResourcePath() + mapName;
    std::string path = "/home/mario/CLionProjects/game/cmake-build-debug/src/res/";
    std::string location = path + mapName;
    std::cout << location << std::endl;

    std::ifstream map;
    map.open(location);
    unsigned long mapHeight = getMapHeight(map);
    unsigned long mapWidth = getMapLength(map);

    std::cout << "Height " << mapHeight << std::endl;
    std::cout << "Width " << mapWidth << std::endl;

    auto* entityController = new class entityController();

    readMap(map, entityController);
    entityController->printEntities();


}

unsigned long TXTParser::getMapHeight(std::ifstream& map) {
    std::string Dummy;
    unsigned long mapHeight = 0;

    while(!map.eof()) {
        getline(map, Dummy);
        mapHeight++;
    }
    //Reset Position to counterfeit side effect
    map.seekg(0);
    return mapHeight;
}

unsigned long TXTParser::getMapLength(std::ifstream& map) {
    std::string Dummy;
    unsigned long mapWidth = 0;

    while(!map.eof()) {
        getline(map, Dummy);
        if (mapWidth < Dummy.size())
            mapWidth = Dummy.size();
    }
    //Reset Position to counterfeit side effect
    map.seekg(0);
    return mapWidth;
}

void TXTParser::readMap(std::ifstream &map, entityController *entityController) {
    int line = 0;
    while(!map.eof()) {
        std::string currentLine;
        getline(map, currentLine);
        auto* dimension = new class dimension(1, 1);
        for (int i = 0; i < (int) currentLine.length(); i++) {
            if (currentLine[i] == '_') {
                auto* position = new class position(i, line);
                entityController->createEntity(1000, position, dimension);
            }
        }
        line++;
    }
}
