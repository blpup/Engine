#pragma once
#include <vector>
#include "GamePhysics.h"
#include "GameObjectHandler.h"
#include "Vector2.h"
#include "UUID.h"
#include <GLFW/glfw3.h>

namespace GameEngine {
	//This struct defines game objects to support DOD.
	struct GameObjectDef {
		//Defaults
		GameObjectDef() {
			position.SetVector2(0.f, 0.f);
			GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
			ObjectHandler.Add(*this);
		};
		UUID id;
		Vector2 position;
	};

	//A class to accompany the struct.
	//Provides as a wrapper to help make any modifications to a provided game object.
	class GameObject
	{
	public:
		GameObject(const GameObjectDef* object);
		GameObject(const GameObjectDef* object, uint64_t id);
		~GameObject();
		virtual void Update();
		virtual void Destroy();
		Vector2 GetCoords() const;
		void SetCoords(float x, float y);
		uint64_t GetID() const;
	private:
		uint64_t m_id;
		Vector2 m_position;
	};
}


