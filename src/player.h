#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entity.h"
#include "position.h"
#include "dimension.h"

class player : entity{
public:
    player(int health, class position* position, class dimension* dimension);

    void jump();
private:

};


#endif //GAME_PLAYER_H
