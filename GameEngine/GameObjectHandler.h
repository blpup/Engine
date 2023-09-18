#pragma once
#include <vector>

namespace GameEngine {
	class UUID;
	class GameObject;
	struct GameObjectDefinition;

	class GameObjectHandler
	{
	public:
		GameObjectHandler(GameObjectHandler& other) = delete;
		void operator=(const GameObjectHandler&) = delete;
		static GameObjectHandler& GetInstance();
		void Add(GameObjectDefinition& component);
		void Remove(GameObject* component);
		void Render();
		size_t GetGameObjectIndex(uint64_t id);
		GameObjectDefinition& GetGameObject(size_t index);
	private:
		GameObjectHandler(void){}
		std::vector<GameObjectDefinition*> m_objects;
	};
}


