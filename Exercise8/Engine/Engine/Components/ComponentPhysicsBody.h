#pragma once

#include "Engine/Component.h"

#include <Box2D/Box2D.h>

class ComponentPhysicsBody : public MyEngine::Component {
	friend class MyEngine::Engine; // TODO get rid of this

public:
	~ComponentPhysicsBody();

	virtual void Init(rapidjson::Value& serializedData) override;

	void CreateBody(b2BodyType bodyType, bool isSensor, glm::vec2 size);
	// Force gradually affects the velocity over time
	void addForce(glm::vec2 force);
	// Instantly affects velocity
	void addImpulse(glm::vec2 impulse);
	void setLinearVelocity(glm::vec2 velocity);
	glm::vec2 getLinearVelocity();

private:
	b2World* _world;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	b2PolygonShape* _shape = nullptr;
};