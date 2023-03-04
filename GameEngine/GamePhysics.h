#pragma once
#include <vector>
#include "Enums.h"

namespace GameEngine {
	class PhysicsComponent;

	class GamePhysics
	{
	public:
		GamePhysics(GamePhysics& other) = delete;
		void operator=(const GamePhysics&) = delete;
		static GamePhysics& GetInstance();
		void Add(PhysicsComponent* component);
		void Remove(PhysicsComponent* component);
		void Render();
		PhysicsComponent* GetPhysicsComponentByID(int id);
	private:
		GamePhysics(void){}
		void UpdateMovability(struct PhysicsObject* object, Direction direction);
		float Bisection(PhysicsComponent& PComponent1, PhysicsComponent& PComponent2, float speed);
		void CalculateNextStep(PhysicsComponent& PComponent1, PhysicsComponent& PComponent2);
		int CheckCollision(float deltaX, float deltaY, float width1, float height1, float width2, float heigth2) const;

		Direction CollisionDirection(PhysicsComponent& object, PhysicsComponent& other) const;
		std::vector<PhysicsComponent*> Objects;
		bool b_nextStepCollisionTriggered = false;
	};
}


