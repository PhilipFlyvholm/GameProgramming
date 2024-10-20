#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class LaserController : public MyEngine::Component {
		const float MovAmount = 50;
		glm::vec2 direction = glm::vec2(1, 0);

	public:
		glm::vec2 position;
		float rotation;

		void Init() override;
		void Update(float) override;
	};
}