#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"
#include "Engine/DeserializationLib.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
	physicsBody = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>().lock();
	impluse_strength = serializedData["impulseStrength"].GetFloat();
	linearVelocity = MyEngine::DeserializeVector2(serializedData["linearVelocity"]);
	physicsBody->setLinearVelocity(linearVelocity);
}

void ComponentController::Update(float deltaTime) {
	// TODO, if you need to do anything here
	if (dead) {
		physicsBody->setLinearVelocity({ 0, 0 });
	}
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_SPACE) {
		if (event.type == SDL_KEYDOWN && !jump) {
			physicsBody->addImpulse(glm::vec2(0, impluse_strength));
			jump = true;
		}
		if(event.type == SDL_KEYUP){
			jump = false;
		}
	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
	printf("Collision with %s\n", other->GetGameObject().lock()->GetName().c_str());
	dead = true;
	
}