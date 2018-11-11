#ifndef GAME_DIMENSION_H
#define GAME_DIMENSION_H

//Used to describe the size in space of an object
class dimension {
public:
    dimension(int xDimension, int yDimension);
    dimension();
    void setDimension(int xDimension, int yDimension);
    int getXDimension();
    int getYDimension();

private:
    int xDimension;
    int yDimension;

};


#endif //GAME_DIMENSION_H
