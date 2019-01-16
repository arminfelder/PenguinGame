//
// Created by armin on 16.01.19.
//

#ifndef GAME_CANCOLLECT_H
#define GAME_CANCOLLECT_H

#include <vector>
#include "Component.h"
#include "Inventory.h"

namespace Components {
    class CanCollect: public Component {
    public:
        CanCollect(const std::set<Inventory::ItemTypes> &pTypes);
        std::set<Inventory::ItemTypes> mTypes;
    };
}


#endif //GAME_CANCOLLECT_H
