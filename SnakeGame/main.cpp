#include <iostream>
#include <chrono>
#include <random>
#include "config.h"
#include "ITUGames.h"
#include <vector>
#include "position.h"
#include "player.h"
#include "item.h"

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
std::vector<Item> items;
const int TARGET_FPS = 60;
constexpr double TARGET_TIME_ELAPSED = 1.0 / TARGET_FPS;


#pragma endregion // Engine State

#pragma region Game State

/**
 * If you are unsure how to organize the additional variables you will need for the exercise, just dump them here.We will address this in future lectures
 * In the meantime, a good approach is to sort them and put the ones that relate to the same thing together
 * - is this variable part of the game? Of the engine? ...
 * - is it about input? Player state? Logging? ...
 * And so on. Are some of those questions conflicting with each other? Yep, architecturing code is hard, but we'll get a hang of it.
 */

Player player(6, 5, to_be_cleared);

#pragma endregion // Game State


int getRandomInt(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

int main()
{
	// setup
	std::srand(std::time(nullptr)); // initializes random generator
	itr = 0;
	ITUGames::Console::ClearScreen();
	ITUGames::Console::HideCursor();
	items.push_back(Item({10, 5}, 'X'));
	while (true)
	{
		frame_time = std::chrono::steady_clock::now() - time_start;
		time_start = std::chrono::steady_clock::now();

		ProcessEvents();
		Update();
		Render();
		time_end = std::chrono::steady_clock::now();
		time_elapsed = time_end - time_start;
		ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(TARGET_TIME_ELAPSED - time_elapsed.count()));
	}
	return 0;
}

void ProcessEvents()
{
	char c = ITUGames::Console::GetCharacter(false);
	player.process_key_press(c);
	int hits = 0;
	for (auto it = items.begin(); it != items.end();)
	{
		Item item = *it;
		bool collide = player.check_collide(item.get_position());
		if (collide)
		{
			it = items.erase(it);
			hits++;
			player.addBody();
		}
		else
		{
			++it; // Move to the next element if no erasure occurs
		}
	}
	for (int i = 0; i < hits; i++)
	{
		int x = getRandomInt(0, CONSOLE_WIDTH);
		int y = getRandomInt(4, CONSOLE_HEIGHT);
		items.push_back(Item({x,y}, 'X'));
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
	
	for (int i = 0; i < to_be_cleared.size(); i++)
	{
		Position clearPos = to_be_cleared.at(i);
		ITUGames::Console::GotoCoords(clearPos.x, clearPos.y);
		ITUGames::Console::RenderCharacter(' ');
	}
	to_be_cleared.clear();

	for (int i = 0; i < items.size(); i++)
	{
		Item item = items.at(i);
		item.render();
	}

	player.render();
	ITUGames::Console::GotoCoords(CONSOLE_WIDTH, CONSOLE_HEIGHT);
}
