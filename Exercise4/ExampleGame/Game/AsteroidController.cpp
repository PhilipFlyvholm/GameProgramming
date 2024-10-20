#include "AsteroidController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void AsteroidController::Init() {
		glm::vec2 screenSize = MyEngine::Engine::GetInstance()->GetScreenSize();
		const int x = std::rand() % static_cast<int>(screenSize.x);
		const int y = std::rand() % static_cast<int>(screenSize.y);
		glm::vec2 basePos = glm::vec2(x, y);
		GetGameObject()->position = basePos + MovDirection * MovAmount;

		direction = std::rand() % 360;
		RotSpeed = std::rand() % 100 - 50;
	}

	void AsteroidController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();


		glm::vec2 basePos = engine->GetScreenSize() / 2.f;
		MovDirection.x = glm::sin(glm::radians(-direction));
		MovDirection.y = glm::cos(glm::radians(-direction));
		glm::normalize(MovDirection);

		parent->position += MovDirection * MovAmount * deltaTime;
		parent->rotation += RotSpeed * deltaTime;
		const int offset = 30;
		if (parent->position.x < -offset) {
			parent->position.x = engine->GetScreenSize().x + offset;
		}
		if (parent->position.x > engine->GetScreenSize().x + offset) {
			parent->position.x = -offset;
		}
		if (parent->position.y < -offset) {
			parent->position.y = engine->GetScreenSize().y + offset;
		}
		if (parent->position.y > engine->GetScreenSize().y + offset) {
			parent->position.y = -offset;
		}
	}

}