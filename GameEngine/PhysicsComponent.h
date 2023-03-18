#pragma once
#include <vector>
#include "UUID.h"

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
		Movablitiy() {
			forward = 1;
			backward = 1;
			left = 1;
			right = 1;
		}
		Movablitiy(int f, int b, int l, int r) {
			forward = f;
			backward = b;
			left = l;
			right = r;
		}
		int forward;
		int backward;
		int left;
		int right;
	};

	struct PhysicsObject {
		//Defaults
		PhysicsObject() {
			collision = Collision::CAN_COLLIDE;
			collisionType = CollisionType::SOLID;
			width = 0.1f;
			height = 0.1f;
			velocity = 0.0f;
		}
		Collision collision;
		CollisionType collisionType;
		Movablitiy move;
		float width;
		float velocity;
		float height;
		UUID id;
		uint64_t parentId;
	};

	class PhysicsComponent
	{
	public:
		PhysicsComponent(const PhysicsObject* object);
		PhysicsComponent(const PhysicsObject* object, uint64_t id);
		void instantiate(PhysicsObject* object);
		Collision getCollision();
		void setCollision(Collision value);
		CollisionType getCollisionType();
		void setCollisionType(CollisionType value);
		Movablitiy getMovablitiy();
		void setMovablitiy(Movablitiy value);
		float getWidth();
		void setWidth(float value);
		float getHeight();
		void setHeight(float value);
		float getVelocity();
		void setVelocity(float  value);
		uint64_t getID();
		uint64_t getParentID();
	private:
		Collision m_collision;
		CollisionType m_collisionType;
		Movablitiy m_move;
		float m_width;
		float m_height;
		float m_velocity;
		uint64_t m_id;
		uint64_t m_parentId;
	};
}


