#pragma once
#include "position.h"

class Item
{
private:
    char character;
    Position position;

public:
    Item(Position& position, char character);
    void render() const;
    Position get_position();
};