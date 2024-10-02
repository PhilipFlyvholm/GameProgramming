#include <vector>
#include "position.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(int x, int y, std::vector<Position> &to_be_cleared); // Constructor
    void update();
    void process_key_press(char c);
    void render();
    bool check_collide(Position other_pos);
    Position get_position();
    void addBody();
};

#endif // PLAYER_H