#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class ComponentController : public MyEngine::Component {
		const float RotSpeed = 50;
		const float MovSpeed = 5;
		const float MovAmount = 100;//20;
		glm::vec2 MovDirection = glm::vec2(1, 0);
		bool Left = false;
		bool Right = false;
		bool Forward = false;


	public:
		glm::vec2 position;
		float rotaiton;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
	};
}