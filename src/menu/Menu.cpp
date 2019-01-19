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
#include "MenuComponent.h"
#include "MenuEvents.h"
#include "../managers/ComponentsManager.h"


void Menu::create() {
    int position = getMenuSize();
    addMenuComponent(std::make_shared<MenuComponent> ("Sans", "erster Eintrag", "red", position++, MenuEvents::NONE));
    addMenuComponent(std::make_shared<MenuComponent> ("Sans", "New Game", "green", position++,MenuEvents::NEW_GAME));
    addMenuComponent(std::make_shared<MenuComponent> ("Sans", "Exit Menu", "green", position++, MenuEvents::QUIT_MENU));
    addMenuComponent(std::make_shared<MenuComponent> ("Sans", "Quit Game", "green", position++, MenuEvents::QUIT_GAME));
}

void Menu::render(SDL_Renderer* pRenderer) {
    mRunning = true;
    while (mRunning) {
        for (const auto &component : menuComponents) {
            SDL_Rect rect;
            rect.x = 400;
            rect.y = height * (component.second->getPosition() - 1) + 40;
            rect.w = width;
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
                case SDLK_RETURN:
                    triggerMenuEvent();
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
        active = menuComponents.size()-1;
    else if (active >= menuComponents.size())
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
    }
    this->close();
    sendSDLEvent(32780);
}

void Menu::saveGame() {
    std::ofstream out("save.txt");
    Managers::ComponentsManager::saveUserComponents(out);
}

void Menu::loadGame() {
    std::ifstream in("save.txt");
    Managers::ComponentsManager::loadUserComponents(in);
    sendSDLEvent(33334);
}

void Menu::sendSDLEvent(int type) {
    SDL_Event sdl_event;
    sdl_event.type = type;
    SDL_PushEvent(&sdl_event);
}

Menu::Menu() = default;
