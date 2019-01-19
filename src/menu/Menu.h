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

#ifndef GAME_MENU_H
#define GAME_MENU_H


#include <map>
#include <memory>
#include <SDL_surface.h>
#include "MenuComponent.h"
#include <SDL2/SDL.h>
#include "MenuEvents.h"


class Menu {


public:
    void render(SDL_Renderer* pRenderer);
    void close();
    Menu();
    std::map<int, std::shared_ptr<MenuComponent>> getMenuComponents();
    int getMenuSize();
    void addMenuComponent(std::shared_ptr<MenuComponent> component);
private:
    int active = 0;
    std::map<int, std::shared_ptr<MenuComponent>> menuComponents;
    int height = 30, width = 200;
    void handleKeyEvent();
    void triggerMenuEvent();
    void updateSelection(short direction);
    void quitGame();
    void switchMenu(MenuEvents::MenuEventType eventType);
    void saveGame();
    void loadGame();
    void sendSDLEvent(int type);

    bool mRunning = true;

};


#endif //GAME_MENU_H
