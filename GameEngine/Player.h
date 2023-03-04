#pragma once
#include "GameObject.h"

namespace GameEngine {
	class Player : public GameObject
	{
	public:
		Player();
	private:
		class RenderComponent* renderComponent;
		class CircleComponent* circleComponent;
		class PhysicsComponent* physicsComponent;
		class MovementComponent* movementComponent;
	};
}


