#pragma once
#include <vector>
#include "GamePhysics.h"
#include "GameObjectHandler.h"
#include "Vector2.h"
#include "UUID.h"
#include <GLFW/glfw3.h>

namespace GameEngine {
	struct GameObjectDefinition {
		UUID id;
		Vector2 position{0.f,0.f};
	};

	class GameObject
	{
	public:
		GameObject(const GameObjectDefinition* object);
		GameObject(const GameObjectDefinition* object, uint64_t id);
		~GameObject();
		virtual void Update();
		virtual void Destroy();
		Vector2 GetCoords() const;
		void SetCoords(float x, float y);
		uint64_t GetID() const;
		void instantiate(GameObjectDefinition& object);
	private:
		uint64_t m_id;
		Vector2 m_position;
	};
}


