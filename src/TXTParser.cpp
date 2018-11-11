#include "TXTParser.h"
#include "entityController.h"
//#include "res_path.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


class std::vector<int> TXTParser::parseMap(const char *mapName, class entityController* entityController) {
//    std::string location = getResourcePath() + mapName;
    std::string path = "/home/mario/CLionProjects/game/cmake-build-debug/src/res/";
    std::string location = path + mapName;
    std::cout << location << std::endl;

    std::ifstream map;
    map.open(location);
    auto mapHeight = (int) getMapHeight(map);
    auto mapLength = (int) getMapLength(map);

    std::vector<int> information;
    information.push_back(mapHeight);
    information.push_back(mapLength);

    readMap(map, entityController);
    map.close();

    return information;
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
        auto* dimension = new class dimension(10, 5);
        for (int i = 0; i < (int) currentLine.length(); i++) {
            auto *position = new class position(20*i, 10*line);

            //Defines entities given on the input from map file
            switch (currentLine[i]) {
                case '_':
                    entityController->createEntity(1000, position, dimension);
                    break;
                case '|':
                    entityController->createEntity(2000, position, dimension);
                default:
                    break;
                }
            }
        line++;
    }
}
