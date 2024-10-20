#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class PlayerController : public MyEngine::Component {
		const float RotSpeed = 50;
		const float MovAccelarationSpeed = 100;
		const float MovMaxSpeed = 200;
		float MovAmount = 0;
		glm::vec2 MovDirection = glm::vec2(1, 0);
		bool Left = false;
		bool Right = false;
		bool Forward = false;
		bool fired = false;
		std::shared_ptr<sre::SpriteAtlas> sprite_atlas;


	public:
		PlayerController(std::shared_ptr<sre::SpriteAtlas> atlas);
		glm::vec2 position;
		float rotaiton;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
	};
}