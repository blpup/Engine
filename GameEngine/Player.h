#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"

namespace GameEngine {
	class Player
	{
	public:
		Player();
		GameObjectDefinition m_gameObject;
		PhysicsObject m_physicsObject;
		RenderObject m_renderObject;
		MovementDefinition m_movementObject;
		PlayerDefinition m_playerObject;
	};
}


