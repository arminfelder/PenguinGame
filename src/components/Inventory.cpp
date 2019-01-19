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

std::string Inventory::serialize() {
    std::string output;
    for (const ItemTypes &item : mItems) {
        int type = static_cast<int> (item);
        output += "Inventory;"+std::to_string(type)+"\n";
    }
    return output;
}

bool Inventory::load(std::vector<std::string> splittedStrings) {
    if (splittedStrings[0] == "Inventory" && splittedStrings.size() >= 2) {
        this->addItem(static_cast<Inventory::ItemTypes>(std::stoi(splittedStrings[1])));
        return true;
    }
    return false;
}

void Inventory::reset() {
    mItems.clear();
}

std::string Inventory::getItemTypeDescription(Inventory::ItemTypes itemType) {
    std::string returnValue = mItemDescriptions.find(itemType)->second;
    return returnValue;
}
