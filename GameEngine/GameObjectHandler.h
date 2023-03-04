#pragma once
#include <vector>

namespace GameEngine {
	class GameObject;

	class GameObjectHandler
	{
	public:
		GameObjectHandler(GameObjectHandler& other) = delete;
		void operator=(const GameObjectHandler&) = delete;
		static GameObjectHandler& GetInstance();
		void Add(GameObject* component);
		void Remove(GameObject* component);
		void Render();
		std::vector<GameObject*> GetObjects();
	private:
		GameObjectHandler(void){}
		std::vector<GameObject*> m_objects;
	};
}


