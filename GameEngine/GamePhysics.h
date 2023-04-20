#pragma once
#include <vector>
#include "Enums.h"
#include "Vector2.h"
#include "PhysicsComponent.h"

namespace GameEngine {
	class PhysicsComponent;

	class GamePhysics
	{
	public:
		GamePhysics(GamePhysics& other) = delete;
		void operator=(const GamePhysics&) = delete;
		static GamePhysics& GetInstance();
		void Add(PhysicsObject component);
		void Remove(PhysicsObject* component);
		void Render();
		size_t GetPhysicsComponentIndex(int id);
		PhysicsObject* GetPhysicsObjectByParentId(uint64_t id);
	private:
		GamePhysics(void){
			b_nextStepCollisionTriggered = false;
			m_currentObject = nullptr;
			m_targetObject = nullptr;
		}
		void UpdateMovability(struct PhysicsObject& object, Direction direction);
		float Bisection(float speed);
		void CalculateNextStep();
		int CheckCollision(float deltaX, float deltaY) const;
		void DoCollisionSteps();
		Vector2 CalculateDeltas();
		Direction CollisionDirection(PhysicsObject* o1, PhysicsObject* o2) const;
		std::vector<PhysicsObject> Objects;
		bool b_nextStepCollisionTriggered;
		PhysicsObject* m_currentObject;
		PhysicsObject* m_targetObject;
	};
}


