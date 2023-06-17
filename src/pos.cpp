#include "pos.h"


Pos::Pos()
    : x('a')
    , y(1)
    {}

Pos::Pos(int posX, char posY)
    : x(posX)
    , y(posY)
    {}

void Pos::setPos(int posX, char posY) {
    x = posX;
    y = posY;
}

void Pos::setPos(const Pos &pos){
    x = pos.getX();
    y = pos.getY();
}

void Pos::setX(int posX) {
    x = posX;
}

void Pos::setY(char posY) {
    y = posY;
}

int Pos::getX() const {
    return x;
}

char Pos::getY() const {
    return y;
}

bool Pos::operator==(const Pos &pos) const {
    if (x == pos.x && y == pos.y)
        return true;
    return false;
}

bool Pos::operator!=(const Pos &pos) const {
    if (*this == pos)
        return false;
    return true;
}

int Pos::XInBoard() const {
    return x - 1;
}

int Pos::YInBoard() const {
    return y - 97;
}

Pos::Pos(int posX, int posY) {
    x = posX;
    y = char(posY);
}
