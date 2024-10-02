#include <chrono>
#include <vector>
#include "config.h"
#include "ITUGames.h"
#include "position.h"

#define TIME_BETWEEN_CHARACTER_SWITCH 0.25
#define TIME_BETWEEN_MOVE 0.25

class Player
{
private:
    Position player_position;
    std::vector<Position> body_relatives;
    std::chrono::time_point<std::chrono::steady_clock> last_character_switch;
    std::chrono::time_point<std::chrono::steady_clock> last_player_move;
    char character = 'E';
    std::vector<Position> &to_be_cleared;
    Position cur_direction = {1, 0};
    void move();
    void (*handleDeath)();

public:
    Player(int x, int y, std::vector<Position> &to_be_cleared);
    void update();
    void process_key_press(char c);
    void render();
    Position get_position();
    void addBody();
    bool check_collide(Position other_pos);
};

Player::Player(int x, int y, std::vector<Position> &to_be_cleared)
    : to_be_cleared(to_be_cleared)
{
    player_position = {x, y};
}

Position Player::get_position()
{
    return player_position;
}

bool Player::check_collide(Position other_pos)
{
    if (player_position.x == other_pos.x && player_position.y == other_pos.y)
        return true;
    for (int i = 0; i < body_relatives.size(); i++)
    {
        Position body_relative = body_relatives.at(i);
        Position actual_position = {player_position.x + body_relative.x, player_position.y + body_relative.y};
        if (actual_position.x == other_pos.x && actual_position.y == other_pos.y)
            return true;
    }

    return false;
}

void Player::move()
{
    player_position.x = player_position.x + cur_direction.x;
    player_position.y = player_position.y + cur_direction.y;

    if (body_relatives.size() > 0)
    {
        Position last_pos = body_relatives.at(0);
        to_be_cleared.push_back({last_pos.x, last_pos.y});
        body_relatives.erase(body_relatives.begin());
        addBody();
    }
    else
    {
        to_be_cleared.push_back({player_position.x - cur_direction.x, player_position.y - cur_direction.y});
    }
    if (player_position.x < 0)
    {
        player_position.x = CONSOLE_WIDTH;
    }
    if (player_position.x > CONSOLE_WIDTH)
    {
        player_position.x = 0;
    }
    if (player_position.y < 0)
    {
        player_position.y = CONSOLE_HEIGHT;
    }
    if (player_position.y > CONSOLE_HEIGHT)
    {
        player_position.y = 0;
    }
    last_character_switch = std::chrono::steady_clock::now();
}

void Player::addBody()
{
    body_relatives.push_back({player_position.x - cur_direction.x, player_position.y - cur_direction.y});
}
void Player::process_key_press(char c)
{
    switch (c)
    {
    case ITUGames::Console::KEY_W:
        if (cur_direction.x == 0 && cur_direction.y == 1)
            break;
        cur_direction = {0, -1};
        break;
    case ITUGames::Console::KEY_A:
        if (cur_direction.x == 1 && cur_direction.y == 0)
            break;
        cur_direction = {-1, 0};
        break;
    case ITUGames::Console::KEY_D:
        if (cur_direction.x == -1 && cur_direction.y == 0)
            break;
        cur_direction = {1, 0};
        break;
    case ITUGames::Console::KEY_S:
        if (cur_direction.x == 0 && cur_direction.y == -1)
            break;
        cur_direction = {0, 1};
        break;
    default:
        break;
    }
}

void Player::render()
{
    ITUGames::Console::GotoCoords(player_position.x, player_position.y);
    ITUGames::Console::RenderCharacter(character);
    Position cur_position = {player_position.x, player_position.y};
    for (int i = 0; i < body_relatives.size(); i++)
    {
        Position body_pos = body_relatives.at(i);
        ITUGames::Console::GotoCoords(body_pos.x, body_pos.y);
        ITUGames::Console::RenderCharacter(character);
    }
}

void Player::update()
{
    std::chrono::time_point<std::chrono::steady_clock> time_now = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_since_last_switch = time_now - last_character_switch;
    std::chrono::duration<double> time_since_last_move = time_now - last_player_move;
    if (time_since_last_move.count() >= TIME_BETWEEN_MOVE)
    {
        move();
        last_player_move = time_now;
    }
    if (time_since_last_switch.count() >= TIME_BETWEEN_CHARACTER_SWITCH)
    {
        if (character == 'V')
        {
            character = 'D';
        }
        else
        {
            character = 'V';
        }
        last_character_switch = time_now;
    }
}