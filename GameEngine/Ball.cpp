#include "Ball.h"
#include "GamePhysics.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include <vector>
#include "Observer.h"
#include <iostream>
#include <memory>

GameEngine::Ball::Ball()
{
	GameObject goWrapper(&m_gameObject);

	m_gameObject.position.SetVector2(0.1f, 0.2f);
	m_renderObject.parentId = goWrapper.GetID();
	m_movementObject.parentId = goWrapper.GetID();
	m_physicsObject.parentId = goWrapper.GetID();
	m_rotationObject.parentId = goWrapper.GetID();
	m_renderObject.color = Color3(0.f, 1.0f, 0.0f);
	m_renderObject.vertices = CircleComponent(.05f, goWrapper.GetCoords()).GetVertices();
	m_movementObject.speed = .005f;
	m_movementObject.movement.left = 1;

	auto OnCollide = [&](const GameObjectDefinition* otherObject) {
		if (Entity::hasComponent(otherObject->id, Entity::ComponentId::Player) == 1) {
			if (m_movementObject.movement.right == 1) {
				m_movementObject.movement.left = 1;
				m_movementObject.movement.right = 0;
			}
			else {
				m_movementObject.movement.left = 0;
				m_movementObject.movement.right = 1;
			}
		}

		if (otherObject->position.y < 0.5f) {
			m_movementObject.movement.down = 0;
			m_movementObject.movement.up = 1;
			m_movementObject.sinAngle = (rand() % 180 + 1);
		}
		else {
			m_movementObject.movement.down = 1;
			m_movementObject.movement.up = 0;
			m_movementObject.sinAngle = (rand() % 180 + 1);
		}
	};
	OnCollideObserver obs(OnCollide, m_gameObject.id);
	PhysicsSubject::GetInstance().Attach(obs);
	Entity::registerComponent(m_gameObject.id, Entity::ComponentId::Rotation);

	goWrapper.instantiate(m_gameObject);
	RenderComponent(&m_renderObject).instantiate(&m_renderObject);
	PhysicsComponent(&m_physicsObject).instantiate(&m_physicsObject);
	MovementComponent(&m_movementObject).instantiate(&m_movementObject);
}