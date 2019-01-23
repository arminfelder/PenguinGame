//
// Created by armin on 16.01.19.
//

#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include "Component.h"

namespace Components {
    class Inventory:public Component {

    public:
        enum class ItemTypes{
            none,
            keyArea2
        };
        Inventory();
        void addItem(const ItemTypes pItem);
        bool hasItem(const ItemTypes &pItem);
        void removeItem(const ItemTypes &pItem);
        const std::vector<std::string> listItems() const;
        std::string getItemTypeDescription(ItemTypes itemType);
        std::string serialize();
        bool load(std::vector<std::string> splittedStrings);
        void reset();
    private:
        std::set<ItemTypes> mItems;
        std::map<ItemTypes, std::string> mItemDescriptions{{ItemTypes::keyArea2,"Key for Area2"}};
    };
}


#endif //GAME_INVENTORY_H
