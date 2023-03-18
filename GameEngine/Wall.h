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
		class BoxComponent* boxComponent;
		GameObjectDef m_gameObject;
		PhysicsObject m_physicsObject;
		RenderObject m_renderObject;
		MovementDef m_movementObject;
	};
}


