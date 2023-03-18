#pragma once
#include <vector>
#include "RenderComponent.h"
namespace GameEngine {
	class GameRenderer {
	public:
		GameRenderer(GameRenderer& other) = delete;
		void operator=(const GameRenderer&) = delete;
		static GameRenderer& GetInstance();
		void Add(RenderObject* object);
		void Remove(RenderObject* object);
		void Render();
		int GetSize();
	private:
		GameRenderer(void) {}
		std::vector<RenderObject*> Objects;
		void Sort();
	};
}


