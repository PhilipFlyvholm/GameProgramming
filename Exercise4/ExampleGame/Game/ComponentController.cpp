#include "ComponentController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void ComponentController::Init() {
		glm::vec2 basePos = MyEngine::Engine::GetInstance()->GetScreenSize() / 2.f;
		GetGameObject()->position = basePos + MovDirection * MovAmount;
	}

	void ComponentController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

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
		if (Forward) {
			parent->position += MovDirection * MovAmount * deltaTime;
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

	void ComponentController::KeyEvent(SDL_Event& e) {
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
		}
	}

}