#pragma once
#include <vector>
namespace GameEngine {
	class GameObject;
	class RenderComponent;

	class GameRenderer {
	public:
		GameRenderer(GameRenderer& other) = delete;
		void operator=(const GameRenderer&) = delete;
		static GameRenderer& GetInstance();
		void Add(RenderComponent* component);
		void Remove(RenderComponent* component);
		void Render();
		int GetSize();
	private:
		GameRenderer(void) {}
		std::vector<RenderComponent*> Objects;
		void Sort();
	};
}


