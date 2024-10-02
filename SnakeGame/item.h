#ifndef ITEM_H
#define ITEM_H

#include "position.h"

class Item
{
private:
    char character;
    Position position;

public:
    Item(Position position, char character);
    void render();
    Position get_position();
};

#endif