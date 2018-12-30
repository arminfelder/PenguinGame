//
// Created by armin on 07.12.18.
//

#ifndef GAME_HEALTH_H
#define GAME_HEALTH_H


#include "Component.h"
namespace Components{
    class Health : Component {
    public:
        Health(int pHealth);
        int getHealth();

        void setHealth(int health);

        void operator++();

        void operator--();

    private:
        int mHealth;
    };
}


#endif //GAME_HEALTH_H
