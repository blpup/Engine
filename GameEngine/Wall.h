#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"

namespace GameEngine {
	class Wall
	{
	public:
		Wall();
		Wall(float w, float h);
		std::unique_ptr<BoxComponent> boxComponent;
		GameObjectDefinition m_gameObject;
		PhysicsObject m_physicsObject;
		RenderObject m_renderObject;
		MovementDefinition m_movementObject;
	private:
		void init();
	};
}


