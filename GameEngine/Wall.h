#pragma once
#include "GameObject.h"
namespace GameEngine {
	class Wall : public GameObject
	{
	public:
		Wall();
		class RenderComponent* renderComponent;
		class BoxComponent* boxComponent;
		class PhysicsComponent* physicsComponent;
		class MovementComponent* movementComponent;
	};
}


