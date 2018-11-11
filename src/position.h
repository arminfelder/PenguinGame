#ifndef GAME_POINT_H
#define GAME_POINT_H


class position {
public:
    position(int xPosition, int yPosition);
    position();
    void setPosition(int xPosition, int yPosition);
private:
    int xPosition;
    int yPosition;

};


#endif //GAME_POINT_H
