#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/PlayerController.h"
#include "Game/AsteroidController.h"
#include "Game/ComponentRendererSprite.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();
void spawnPlayer();
void spawnAsteroid();

MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(800, 600);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");
	spawnPlayer();
	for (int i = 5; i > 0; i--)
	{
		spawnAsteroid();
	}
	engine.Init();
	
	renderer.startEventLoop();
}

void spawnPlayer() {
	auto gameObject = engine.CreateGameObject("Player");
	auto playerController = std::shared_ptr<ExampleGame::PlayerController>(new ExampleGame::PlayerController(atlas));
	auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	gameObject->AddComponent(playerController);
	gameObject->AddComponent(componentRenderer);

	componentRenderer->sprite = atlas->get("playerShip1_blue.png");
}

void spawnAsteroid() {
	auto gameObject = engine.CreateGameObject("Asteroid");
	auto controller = std::shared_ptr<ExampleGame::AsteroidController>(new ExampleGame::AsteroidController());
	auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	gameObject->AddComponent(controller);
	gameObject->AddComponent(componentRenderer);
	componentRenderer->sprite = atlas->get("Meteors/meteorBrown_big1.png");
}

void ProcessEvents(SDL_Event& event) {
	engine.ProcessEvents(event);	
}

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}