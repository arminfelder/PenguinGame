#include "penguinGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "world.h"

int mult = 20;

int penguinGame::main(int, char **) {
    return 0;
}

int main() {
    auto * world1 = new world();
    world1->create(1920, 1080);
    world1->~world();
};