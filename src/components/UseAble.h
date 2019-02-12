//
// Created by armin on 16.01.19.
//

#ifndef GAME_USEABEL_H
#define GAME_USEABEL_H

#include "Component.h"
#include "Inventory.h"

namespace Components {
    class UseAble: public Component {
    public:
        UseAble(const std::vector<Inventory::ItemTypes> &pItems );
        std::vector<Inventory::ItemTypes> mRequiresItems;
    };
}


#endif //GAME_USEABEL_H
