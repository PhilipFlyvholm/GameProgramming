#pragma once

#include "Engine/Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;

private:
	glm::vec3 _mov;
	float mov_speed;
	float rot_speed;
	float impluse_strength;
	glm::vec2 linearVelocity;
	bool jump = false;
	bool dead = false;
	std::shared_ptr<ComponentPhysicsBody> physicsBody;
};