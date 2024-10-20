#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class AsteroidController : public MyEngine::Component {
		const float MovAmount = 50;
		float RotSpeed = 20;
		glm::vec2 MovDirection = glm::vec2(1, 0);
		float direction = 1;

	public:
		glm::vec2 position;
		float rotaiton;

		void Init() override;
		void Update(float) override;
	};
}