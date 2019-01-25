/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <memory>

#include <algorithm>
#include "Menu.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MenuComponent.h"
#include "MenuEvents.h"
#include "../managers/ComponentsManager.h"


void Menu::render(SDL_Renderer* pRenderer) {
    mRunning = true;
    while (mRunning) {
        for (const auto &component : menuComponents) {
            SDL_Rect rect;
            rect.x = 400;
            rect.y = height * (component.second->getPosition() - 1) + 40;
            rect.w = component.second->getCharsCount()*20 ;
            rect.h = height;

            std::shared_ptr<SDL_Surface> surface = component.second->getSurface();
            auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, surface.get()), SDL_DestroyTexture);
            SDL_RenderCopy(pRenderer, texture.get(), nullptr, &rect);
        }
        SDL_RenderPresent(pRenderer);
        handleKeyEvent();
        SDL_Delay(static_cast<Uint32> (1000 / 60));
    }
}

void Menu::close() {
    mRunning = false;
}

std::map<int, std::shared_ptr<MenuComponent>> Menu::getMenuComponents() {
    return std::map<int, std::shared_ptr<MenuComponent>>();
}

int Menu::getMenuSize() {
    return static_cast<int>(menuComponents.size());
}

void Menu::addMenuComponent(std::shared_ptr<MenuComponent> component) {
    int newId = static_cast<int>(menuComponents.size());

    menuComponents.insert({newId, component});
}

void Menu::handleKeyEvent() {
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYDOWN)) {
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_DOWN:
                    updateSelection(1);
                    break;
                case SDLK_UP:
                    updateSelection(-1);
                    break;
                case SDLK_m:
                case SDLK_p:
                    this->close();
                    break;
                case SDLK_ESCAPE:
                    quitGame();
                    break;
                case SDLK_RETURN:
                    triggerMenuEvent();
                    break;
                case SDLK_1:
                    this->close();
                    sendSDLEvent(32791);
                    break;
                case SDLK_2:
                    this->close();
                    sendSDLEvent(32792);
                    break;
                case SDLK_3:
                    this->close();
                    sendSDLEvent(32793);
                    break;
                case SDLK_5:
                    this->close();
                    sendSDLEvent(33335);
                    break;
                default: break;
            }
        }
    }

}

void Menu::updateSelection(short direction) {
    auto component = menuComponents.at(active);
    component.get()->updateColor("green");

    (direction >= 0) ? active++ : active--;

    if (active < 0)
        active = static_cast<int>(menuComponents.size()-1);
    else if (active >= static_cast<int>(menuComponents.size()))
        active = 0;
    component = menuComponents.at(active);
    component.get()->updateColor("red");
}

void Menu::triggerMenuEvent() {
    auto event = (menuComponents.at(active)).get()->getMenuEventType();
    switch (event) {
        case MenuEvents::QUIT_GAME:
            quitGame();
            break;
        case MenuEvents::QUIT_MENU:
            this->close();
            break;
        case MenuEvents::NEW_GAME:
            this->close();
            sendSDLEvent(33333);
            break;
        case MenuEvents::MAIN_MENU:
        case MenuEvents::PAUSE_MENU:
            switchMenu(event);
            break;
        case MenuEvents::SAVE_GAME:
            saveGame();
            break;
        case MenuEvents::LOAD_GAME:
            this->close();
            loadGame();
            break;
        default:
            std::cout << "function not implemented" << std::endl;
            break;
    }
}

void Menu::quitGame() {
    this->close();
    sendSDLEvent(SDL_QUIT);
}

void Menu::switchMenu(MenuEvents::MenuEventType event) {
    switch (event) {
        case MenuEvents::MAIN_MENU:
            sendSDLEvent(32769);
            break;
        case MenuEvents::PAUSE_MENU:
            sendSDLEvent(32770);
            break;
        default:
            return; //if wrong event type got here, do nothing (should never be the case anyways)
    }
    this->close();
    sendSDLEvent(32780);
}

void Menu::saveGame() {
    std::ofstream out("save.txt");
    Managers::ComponentsManager::saveUserComponents(out);
    out.close();
}

void Menu::loadGame() {
    std::ifstream in("save.txt");
    if (Managers::ComponentsManager::loadUserComponents(in)) //check if loading the map would work
        sendSDLEvent(33334);
    else
        sendSDLEvent(33333); //create new game if loading went wrong
    in.close();
}

void Menu::sendSDLEvent(int type) {
    SDL_Event sdl_event;
    sdl_event.type = static_cast<Uint32>(type);
    SDL_PushEvent(&sdl_event);
}

void Menu::clear() {
    menuComponents.clear();
}

void Menu::updateInventory() {
    //first, delete all inventory elements
    for (const auto &menuComponent : menuComponents) {
        if (menuComponent.second->isItem())
            menuComponents.erase(menuComponent.first);
    }

    //and now insert again
    auto playerInventory = Managers::ComponentsManager::getInventory(1).get();
    std::string playerInventoryString = playerInventory->serialize();
    std::stringstream inventoryLine(playerInventoryString);
    std::string line;
    while (getline(inventoryLine, line)) {
        std::vector<std::string> splittedStrings = Managers::ComponentsManager::splitString(line, ';');
        auto itemType = static_cast<Components::Inventory::ItemTypes>(std::stoi(splittedStrings[1]));
        std::string inventoryText = playerInventory->getItemTypeDescription(itemType);
        auto position = menuComponents.size() + 1;
        this->addMenuComponent(std::make_shared<MenuComponent>("Sans", inventoryText, "green", position, MenuEvents::NONE, itemType));
    }
    updateStats();
}

void Menu::updateStats() {
    //also write player stats
    auto playerXP = Managers::ComponentsManager::getXp(1);
    auto playerHeatlh = Managers::ComponentsManager::getHealthComponent(1);
    auto playerEvadeCap = Managers::ComponentsManager::getEvadeCapability(1);
    auto position = menuComponents.size() + 2;

    std::string xpText = "XP: " + std::to_string(playerXP->mXp);
    std::string healthText = "Health: " + std::to_string(playerHeatlh->mHealth);
    std::string evadeText = "Evade capability: " + std::to_string(playerEvadeCap->mChance);
    auto itemType = Components::Inventory::ItemTypes::none; // use already implemented delete feature to update stats
    this->addMenuComponent(std::make_shared<MenuComponent>("Sans", xpText, "green", position++, MenuEvents::NONE, itemType));
    this->addMenuComponent(std::make_shared<MenuComponent>("Sans", healthText, "green", position++, MenuEvents::NONE, itemType));
    this->addMenuComponent(std::make_shared<MenuComponent>("Sans", evadeText, "green", position++, MenuEvents::NONE, itemType));

}

Menu::Menu() = default;
