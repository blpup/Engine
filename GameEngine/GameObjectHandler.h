#pragma once
#include <vector>

namespace GameEngine {
	class UUID;
	class GameObject;
	struct GameObjectDef;

	class GameObjectHandler
	{
	public:
		GameObjectHandler(GameObjectHandler& other) = delete;
		void operator=(const GameObjectHandler&) = delete;
		static GameObjectHandler& GetInstance();
		void Add(GameObjectDef& component);
		void Remove(GameObject* component);
		void Render();
		size_t GetGameObjectIndex(uint64_t id);
		GameObjectDef& GetGameObject(size_t index);
	private:
		GameObjectHandler(void){}
		std::vector<GameObjectDef*> m_objects;
	};
}


