#pragma once
#include <vector>
#include <memory>
#include "RenderComponent.h"
namespace GameEngine {
	class GameRenderer {
	public:
		GameRenderer(GameRenderer& other) = delete;
		void operator=(const GameRenderer&) = delete;
		static GameRenderer& GetInstance();
		void Add(RenderObject* object);
		void Remove(RenderObject* object);
		void Render(std::unique_ptr<class OrthographicCamera>& camera);
		int GetSize();
		void GenerateBuffers();
	private:
		GameRenderer(void) {}
		void CalculateRenderPosition(std::vector<Vertex>& vertices, Vector2 position);
		std::vector<RenderObject*> Objects;
		void Sort();
		unsigned int mainBuffer;
	};
}


