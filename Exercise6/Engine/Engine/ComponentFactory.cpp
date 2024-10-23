#include "ComponentFactory.h"

namespace MyEngine {
	std::map<std::string, std::function<std::shared_ptr<MyEngine::Component>()>> ComponentFactory::_componentMap = { };

	void ComponentFactory::RegisterComponentOfType(std::string typeId, std::function<std::shared_ptr<MyEngine::Component>()> builder) {
		_componentMap[typeId] = builder;
	}

	std::shared_ptr<MyEngine::Component> ComponentFactory::GetComponentOfType(std::string typeId) {
		return _componentMap[typeId]();
	}
}