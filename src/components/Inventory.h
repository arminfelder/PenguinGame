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
#include <memory>

namespace Components {
    class Inventory:public Component {

    public:
        enum class ItemTypes{
            none,
            disc,
            keyArea2,
	        ak47,
	        shield,
	        finger,
	        keyArea1
        };
        Inventory();
        void addItem(const ItemTypes pItem);
        bool hasItem(const ItemTypes &pItem);

        void removeItem(const ItemTypes &pItem);
        template <typename T>
        const std::vector<T> listItems() const {
            std::vector<T> mReturnArray;
            if constexpr(std::is_same<T,std::string>()){
                for(const auto &item: mItems){
                    mReturnArray.emplace_back(mItemDescriptions.find(item)->second);
                }
                return mReturnArray;
            }else if(std::is_same<T, ItemTypes >()) {
                for(const auto &elem: mItems){
                    mReturnArray.emplace_back(elem);
                }


            }
            return mReturnArray;
        }

        std::string getItemTypeDescription(ItemTypes itemType);
        int getItemTypeDistribution(ItemTypes itemType);
        std::string serialize();
        int getDistributionSum(std::shared_ptr<Components::Inventory> entityInventory);
        bool load(std::vector<std::string> splittedStrings);
        void reset();

    private:
        std::set<ItemTypes> mItems;
        std::map<ItemTypes, std::string> mItemDescriptions{{ItemTypes::keyArea2,"Key for Area2"},
                                                           {ItemTypes::disc,"Disc allows to save the game"},
                                                           {ItemTypes::ak47, "Ak47"},
                                                           {ItemTypes::shield, "Shield"},
                                                           {ItemTypes ::keyArea1, "Key for Area1"}};
        std::map<ItemTypes, int> mItemDistribution{{ItemTypes::ak47, 2},
                                                  {ItemTypes::shield, 0},
                                                  {ItemTypes::keyArea2, 0},
                                                  {ItemTypes::disc, 0},
                                                   {ItemTypes::finger, 6},
                                                   {ItemTypes ::keyArea1, 0}};
    };
}


#endif //GAME_INVENTORY_H
