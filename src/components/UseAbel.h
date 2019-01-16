//
// Created by armin on 16.01.19.
//

#ifndef GAME_USEABEL_H
#define GAME_USEABEL_H

#include "Component.h"
#include "Inventory.h"

namespace Components {
    class UseAbel: public Component {
    public:
        UseAbel();
        std::vector<Inventory::ItemTypes> mRequiresItems;
    };
}


#endif //GAME_USEABEL_H
