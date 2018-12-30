//
// Created by armin on 07.12.18.
//

#include "Health.h"
using namespace Components;

void Health::operator++() {
    mHealth++;
}

void Health::operator--() {
    mHealth--;
}

int Health::getHealth() {
    return mHealth;
}

void Health::setHealth(int health) {
    mHealth = health;
}

Health::Health(int pHealth):mHealth(pHealth) {

}
