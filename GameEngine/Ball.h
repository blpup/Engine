#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "Structs.h"

namespace GameEngine {
	class Ball
	{
	public:
		Ball();
		GameObjectDefinition m_gameObject;
		PhysicsObject m_physicsObject;
		RenderObject m_renderObject;
		MovementDefinition m_movementObject;
		RotationDefinition m_rotationObject;
	};
}


