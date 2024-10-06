#include "item.h"
#include "ITUGames.h"

Item::Item(Position& pos, char sym) : position(pos), character(sym) {}

void Item::render() const {
    ITUGames::Console::GotoCoords(position.x, position.y);
    ITUGames::Console::RenderCharacter(character);
}

Position Item::get_position() {
    return position;
}