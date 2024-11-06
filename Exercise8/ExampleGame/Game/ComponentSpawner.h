#pragma once

#include "Engine/Component.h"

class ComponentSpawner : public MyEngine::Component {
	void Init(rapidjson::Value&) override;

	void SpawnWall(std::string name, std::string sprite, glm::vec3 pos);

	void SpawnFloor(int width, glm::vec3 pos);
};