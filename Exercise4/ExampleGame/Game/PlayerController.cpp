#include "PlayerController.h"
#include "LaserController.h"
#include "Engine/MyEngine.h"
#include "ComponentRendererSprite.h"

namespace ExampleGame {


	PlayerController::PlayerController(std::shared_ptr<sre::SpriteAtlas> atlas)
	{
		sprite_atlas = atlas;
	}

	void PlayerController::Init() {
		glm::vec2 basePos = MyEngine::Engine::GetInstance()->GetScreenSize() / 2.f;
		GetGameObject()->position = basePos + MovDirection * MovAmount;
	}

	void PlayerController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();


		if (Forward) {
			MovAmount += MovAccelarationSpeed * deltaTime;
			if (MovAmount > MovMaxSpeed) {
				MovAmount = MovMaxSpeed;
			}
		}
		else {
			MovAmount -= MovAccelarationSpeed*2 * deltaTime;
			if (MovAmount < 0) {
				MovAmount = 0;
			}
		}
		glm::vec2 basePos = engine->GetScreenSize() / 2.f;
		MovDirection.x = glm::sin(glm::radians(-parent->rotation));
		MovDirection.y = glm::cos(glm::radians(-parent->rotation));
		glm::normalize(MovDirection);


		if (Left) {
			parent->rotation += RotSpeed * deltaTime;
		}
		if (Right) {
			parent->rotation -= RotSpeed * deltaTime;
		}
		if (MovAmount > 0.1) {
			parent->position += MovDirection * MovAmount * deltaTime;
		}

		if (fired) {
			auto gameObject = engine->CreateGameObject("Laser");
			auto controller = std::shared_ptr<ExampleGame::LaserController>(new ExampleGame::LaserController());
			auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
			gameObject->AddComponent(controller);
			gameObject->AddComponent(componentRenderer);
			componentRenderer->sprite = sprite_atlas->get("Lasers/laserBlue01.png");
			parent->AddChild(std::make_shared<MyEngine::GameObject>(*gameObject));
			fired = false;
			gameObject->position = parent->position;
			gameObject->rotation = parent->rotation;
			gameObject->Init();
		}

		const int offset = 30;
		if (parent->position.x < -offset) {
			parent->position.x = engine->GetScreenSize().x+offset;
		}
		if (parent->position.x > engine->GetScreenSize().x+offset) {
			parent->position.x = -offset;
		}
		if (parent->position.y < -offset) {
			parent->position.y = engine->GetScreenSize().y+offset;
		}
		if (parent->position.y > engine->GetScreenSize().y+offset) {
			parent->position.y = -offset;
		}
	}

	void PlayerController::KeyEvent(SDL_Event& e) {
		switch (e.key.keysym.sym) {
		case SDLK_a:
			Left = e.type == SDL_KEYDOWN;
			break;
		case SDLK_d:
			Right = e.type == SDL_KEYDOWN;
			break;
		case SDLK_w:
			Forward = e.type == SDL_KEYDOWN;
			break;
		case SDLK_SPACE:
			if (e.type == SDL_KEYDOWN) {
				fired = true;
			}
			break;
		}
	}

}