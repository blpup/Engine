#include "Ball.h"
#include "GamePhysics.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include <vector>
#include "Observer.h"
#include <iostream>

GameEngine::Ball::Ball()
{
	GameObject goWrapper(&m_gameObject);
	MovementComponent movWrapper(&m_movementObject);
	circleComponent = new CircleComponent(.05f, goWrapper.GetCoords());

	m_gameObject.position.SetVector2(0.1f, 0.2f);
	m_renderObject.parentId = goWrapper.GetID();
	m_movementObject.parentId = goWrapper.GetID();
	m_physicsObject.parentId = goWrapper.GetID();
	m_renderObject.color = Color3(0.f, 1.0f, 0.0f);
	m_renderObject.vertices = circleComponent->GetVertices();
	movWrapper.SetSpeed(.01f);
	m_movementObject.speed = movWrapper.GetSpeed();
	m_movementObject.movement.left = 1;

	RenderComponent(&m_renderObject).instantiate(&m_renderObject);
	PhysicsComponent(&m_physicsObject).instantiate(&m_physicsObject);
	movWrapper.instantiate(&m_movementObject);

	auto OnCollide = [&](const GameObjectDef* otherObject) {
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
		}
		else {
			m_movementObject.movement.down = 1;
			m_movementObject.movement.up = 0;
		}
	};
	OnCollideObserver obs(OnCollide, m_gameObject.id);
	PhysicsSubject::GetInstance().Attach(obs);
}