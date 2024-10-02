#include "position.h"
#include "ITUGames.h"
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

Item::Item(Position position, char character)
{
    this->position = position;
    this->character = character;
}

void Item::render(){
    ITUGames::Console::GotoCoords(position.x, position.y);
    ITUGames::Console::RenderCharacter(character);
}

Position Item::get_position(){
    return position;
}

