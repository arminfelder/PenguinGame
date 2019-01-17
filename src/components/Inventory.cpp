//
// Created by armin on 16.01.19.
//

#include "Inventory.h"

using namespace Components;
Inventory::Inventory() {

}

void Inventory::addItem(const Inventory::ItemTypes pItem) {
    mItems.insert(pItem);
}

bool Inventory::hasItem(const Inventory::ItemTypes &pItem) {
    return mItems.find(pItem) != mItems.end();
}

void Inventory::removeItem(const Inventory::ItemTypes &pItem) {
    mItems.erase(pItem);
}

const std::vector<std::string> Inventory::listItems() const {
    std::vector<std::string> mReturnArray(mItems.size());
    for(const auto &item: mItems){
        mReturnArray.push_back(mItemDescriptions.find(item)->second);
    }
    return mReturnArray;
}
