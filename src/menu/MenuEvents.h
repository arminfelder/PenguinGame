#ifndef GAME_MENUEVENTS_H
#define GAME_MENUEVENTS_H


class MenuEvents {
public:
    typedef enum{
    QUIT_GAME,
    QUIT_MENU,
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    NONE
} MenuEventType;

};


#endif //GAME_MENUEVENTS_H
