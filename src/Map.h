#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <string>
#include "EntityController.h"

class Map {
public:
    explicit Map(const std::string &mapName);
    class EntityController* getEntityController();
    void draw(SDL_Renderer *renderer, int xOffset, int yOffset);
    void draw(SDL_Renderer* renderer);

private:
    int height;
    int length;
    class EntityController* entityController;
};


#endif //GAME_MAP_H
