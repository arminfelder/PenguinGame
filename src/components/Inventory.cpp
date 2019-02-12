//
// Created by armin on 16.01.19.
//

#include <memory>
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

int Inventory::getItemTypeDistribution(Inventory::ItemTypes itemType) {
    int returnValue = mItemDistribution.find(itemType)->second;
    return returnValue;
}

int Inventory::getDistributionSum(std::shared_ptr<Components::Inventory> entityInventory) {
    auto items = entityInventory->listItems<Components::Inventory::ItemTypes>();

    int distributionSum = 0;
    for (const auto &item : items) {//find length for distributionSum
        distributionSum+=entityInventory->getItemTypeDistribution(item); //sum up here the distribution from inventory.h
    }
    return distributionSum;
}
