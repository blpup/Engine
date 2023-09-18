#pragma once
#include <vector>
#include "UUID.h"
#include "Structs.h"
namespace GameEngine {
	enum class Collision {
		CAN_COLLIDE,
		CANT_COLLIDE
	};
	enum class CollisionType {
		SOLID,
		BOUNCE
	};
	enum class PhysicsType {
		STATIC,
		WORLD
	};

	struct PhysicsObject {
		UUID id;
		uint64_t parentId = NULL;
		float width = 0.1f;
		float height = 0.1f;
		Collision collision = Collision::CAN_COLLIDE;
		CollisionType collisionType = CollisionType::SOLID;;
		PhysicsType physicsType= PhysicsType::STATIC;
		Movablitiy move;
	};

	class PhysicsComponent
	{
	public:
		PhysicsComponent(const PhysicsObject* object);
		PhysicsComponent(const PhysicsObject* object, uint64_t id);
		void instantiate(PhysicsObject* object);
		const Collision getCollision() const;
		void setCollision(Collision value);
		const CollisionType getCollisionType() const;
		void setCollisionType(CollisionType value);
		const Movablitiy getMovablitiy() const;
		void setMovablitiy(Movablitiy value);
		const float getWidth() const;
		void setWidth(float value);
		const float getHeight() const;
		void setHeight(float value);
		const float getVelocity() const;
		void setVelocity(float  value);
		uint64_t getID() const;
		uint64_t getParentID() const;
		void setPhysicsType(PhysicsType value);
		const PhysicsType getPhysicsType();
	private:
		uint64_t m_id;
		uint64_t m_parentId;
		Collision m_collision;
		CollisionType m_collisionType;
		PhysicsType m_physicsType;
		Movablitiy m_move;
		float m_width;
		float m_height;
		float m_velocity;

	};
}


