#pragma once
#include "GameObject.h"

namespace GameEngine {
	class Ball : public GameObject
	{
	public:
		Ball();
		void Update() override;
	private:
		class RenderComponent* renderComponent;
		class CircleComponent* circleComponent;
		class PhysicsComponent* physicsComponent;
		class MovementComponent* movementComponent;
	};
}


