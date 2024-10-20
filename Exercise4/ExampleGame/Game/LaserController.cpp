#include "LaserController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void LaserController::Init() {
		MyEngine::GameObject* self = GetGameObject();
		direction.x = glm::sin(glm::radians(-self->rotation));
		direction.y = glm::cos(glm::radians(-self->rotation));
		glm::normalize(direction);
		GetGameObject()->position = self->position + direction * MovAmount;
	}

	void LaserController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* self = GetGameObject();
		self->position += direction * MovAmount * deltaTime;

		const int offset = 30;
		if (self->position.x < -offset
			|| self->position.x > engine->GetScreenSize().x + offset
			|| self->position.y < -offset
			|| self->position.y > engine->GetScreenSize().y + offset){
//			self->RemoveChild(self_ref);
		}
	}

}