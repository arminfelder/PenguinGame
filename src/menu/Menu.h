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
    void create();
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

    bool mRunning = true;

};


#endif //GAME_MENU_H
