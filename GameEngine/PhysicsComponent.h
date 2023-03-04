#pragma once
#include <vector>
namespace GameEngine {
	enum class Collision {
		CAN_COLLIDE,
		CANT_COLLIDE
	};
	enum class CollisionType {
		SOLID,
		BOUNCE
	};
	struct Movablitiy {
		int forward = 1;
		int backward = 1;
		int left = 1;
		int right = 1;
	};
	struct PhysicsObject {
		Collision m_collision;
		CollisionType m_type;
		Movablitiy m_move;
		float m_width;
		float m_height;
	};
	class PhysicsComponent
	{
	public:
		PhysicsComponent(Collision collision, CollisionType type, float width, float height, class GameObject& object);
		PhysicsObject& GetPhysicsObject();
		void UpdateCollision(Collision collision);
		class GameObject& GetObject();
		Movablitiy CanMove();
		int GetID();
	private:
		PhysicsObject m_physicsObject{};
		GameObject& m_object;
		int m_ID;
	};
}


