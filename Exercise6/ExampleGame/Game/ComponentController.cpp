#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
	printf("%f", serializedData["rotSpeed"].GetFloat());
}

void ComponentController::Update(float deltaTime) {
	auto gameObject = GetGameObject();
	
	if (Forward || Backward) {
		glm::vec3 position = gameObject->GetPosition();
		glm::vec3 move_direction = glm::vec3(0, 0, 0);
		move_direction.x = glm::sin(glm::radians(gameObject->GetEulerAngles().y));
		move_direction.z = glm::cos(glm::radians(gameObject->GetEulerAngles().y));
		glm::normalize(move_direction);
		if (Forward)
			position -= move_direction * mov_speed * deltaTime;
		else if (Backward)
			position += move_direction * mov_speed * deltaTime;
		gameObject->SetPosition(position);
	}

	if (Left || Right) {
		glm::vec3 rotation = gameObject->GetEulerAngles();
		if (Left)
			rotation.y += rot_speed * deltaTime;
		else if (Right)
			rotation.y -= rot_speed * deltaTime;
		gameObject->SetEulerAngles(rotation);
		printf("Rotation speed: %f\n", rot_speed);
	}
}

void ComponentController::KeyEvent(SDL_Event& e)
{
	switch (e.key.keysym.sym) {
	case SDLK_w:
		Forward = e.type == SDL_KEYDOWN;
		break;

	case SDLK_s:
		Backward = e.type == SDL_KEYDOWN;
		break;
	
	case SDLK_a:
		Left = e.type == SDL_KEYDOWN;
		break;
	case SDLK_d:
		Right = e.type == SDL_KEYDOWN;
		break;
	}
}

void ComponentController::Render(sre::RenderPass&) {
	auto gameObject = GetGameObject();
	glm::vec3 position = gameObject->GetPosition();
	glm::vec3 _rotation = gameObject->GetEulerAngles();
	glm::vec3 scale = gameObject->GetScale();

	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 85), ImGuiCond_Always);
	ImGui::Begin("ComponentController::Render", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (ImGui::DragFloat3("Position", &(position.x)))
		gameObject->SetPosition(position);
	if (ImGui::DragFloat3("Rotation", &(_rotation.x)))
		gameObject->SetEulerAngles(_rotation);
	if (ImGui::DragFloat3("Scale", &(scale.x)))
		gameObject->SetScale(scale);
	ImGui::End();
}