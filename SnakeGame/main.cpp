#include <iostream>
#include <chrono>
#include <random>
#include "config.h"
#include "ITUGames.h"
#include <vector>
#include "position.h"
#include "player.h"
#include "item.h"
#include <string>
#include <algorithm>

void Render();
void Update();
void ProcessEvents();
void HandleDeath();

#pragma region Engine State

std::chrono::time_point<std::chrono::steady_clock> time_start;
std::chrono::time_point<std::chrono::steady_clock> time_end;
std::chrono::duration<double> time_elapsed;
std::chrono::duration<double> frame_time;
int itr;
std::vector<Position> to_be_cleared;
std::vector<std::shared_ptr<Item>> items;
const int TARGET_FPS = 60;
constexpr double TARGET_TIME_ELAPSED = 1.0 / TARGET_FPS;

#pragma endregion // Engine State

#pragma region Game State

Player player(6, 5, to_be_cleared);

#pragma endregion // Game State

int getRandomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int main()
{
    // setup
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // initializes random generator
    itr = 0;
    time_start = std::chrono::steady_clock::now();
    ITUGames::Console::ClearScreen();
    ITUGames::Console::HideCursor();
    // Initial item
    items.clear();
    items.shrink_to_fit();
    std::cout << "Size: " << items.size() << ", Capacity: " << items.capacity() << std::endl;
    items.push_back(std::make_shared<Item>(Position{ 10, 5 }, 'X'));
    std::cout << "Size: " << items.size() << ", Capacity: " << items.capacity() << std::endl;

    while (true)
    {
        time_start = std::chrono::steady_clock::now();

        ProcessEvents();
        Update();
        Render();

        time_end = std::chrono::steady_clock::now();
        time_elapsed = time_end - time_start;

        double sleep_duration = TARGET_TIME_ELAPSED - time_elapsed.count();
        if (sleep_duration > 0) {
            ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_duration));
        }

        frame_time = std::chrono::steady_clock::now() - time_start;
    }
    return 0;
}

void ProcessEvents()
{
    try {
        char c = ITUGames::Console::GetCharacter(false);
        player.process_key_press(c);

        // Use indices instead of iterators for more controlled removal
        std::vector<size_t> to_remove;
        for (size_t i = 0; i < items.size(); ++i) {
			Item item = *items[i];
            if (player.check_collide(item.get_position())) {
                to_remove.push_back(i);
            }
        }

        // Remove items and add new ones
        for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
            if (*it < items.size()) {  // Safety check
                items.erase(items.begin() + *it);
                player.addBody();

                // Add new item with bounds checking
                int x = getRandomInt(0, CONSOLE_WIDTH);
                int y = getRandomInt(4, CONSOLE_HEIGHT);
                items.push_back(std::make_shared<Item>(Position{ x,y }, 'X'));
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in ProcessEvents: " << e.what() << std::endl;
    }
}

void Update()
{
    itr++;
    player.update();
}

void Render()
{
    ITUGames::Console::GotoCoords(0, 1);
    ITUGames::Console::ClearLine();
    ITUGames::Console::PrintStr("Elapsed (ms): " + std::to_string(frame_time.count() * 1000.0));
    ITUGames::Console::GotoCoords(0, 2);
    ITUGames::Console::ClearLine();
    ITUGames::Console::PrintStr("FPS:     " + std::to_string(1 / frame_time.count()));
    ITUGames::Console::GotoCoords(0, 3);
    ITUGames::Console::ClearLine();
    ITUGames::Console::PrintStr("Itr:     " + std::to_string(itr));

    for (const auto& clearPos : to_be_cleared) {
        ITUGames::Console::GotoCoords(clearPos.x, clearPos.y);
        ITUGames::Console::RenderCharacter(' ');
    }
    to_be_cleared.clear();

    for (const auto& item : items) {
        (*item).render();
    }

    player.render();
    ITUGames::Console::GotoCoords(CONSOLE_WIDTH - 1, CONSOLE_HEIGHT - 1);
}