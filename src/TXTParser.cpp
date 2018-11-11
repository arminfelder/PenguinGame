#include "TXTParser.h"
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
    //get height:
    unsigned long mapHeight = getMapHeight(map);
    unsigned long mapWidth = getMapLength(map);

    std::cout << "Height " << mapHeight << std::endl;
    std::cout << "Width " << mapWidth << std::endl;

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
