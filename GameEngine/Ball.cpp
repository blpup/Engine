#include "Ball.h"
#include "GamePhysics.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include "Observer.h"
#include <iostream>

GameEngine::Ball::Ball()
{
	GameObject goWrapper(&m_gameObject);
	RenderComponent renWrapper(&m_renderObject);
	MovementComponent movWrapper(&m_movementObject);
	PhysicsComponent phyWrapper(&m_physicsObject);
	circleComponent = new CircleComponent(.05f, goWrapper.GetCoords());

	m_gameObject.position.SetVector2(0.1f, 0.2f);

	m_renderObject.parentId = m_gameObject.id;
	m_movementObject.parentId = m_gameObject.id;
	m_physicsObject.parentId = m_gameObject.id;
	m_renderObject.color = Color3(0.f, 1.0f, 0.0f);
	m_renderObject.vertices = circleComponent->GetVertices();

	renWrapper.instantiate(&m_renderObject);
	movWrapper.instantiate(&m_movementObject);
	phyWrapper.instantiate(&m_physicsObject);
	movWrapper.SetSpeed(.01f);
	m_movementObject.speed = movWrapper.GetSpeed();
	m_movementObject.movement.left = 1;

	PhysicsSubject& PhysicsSubject = PhysicsSubject::GetInstance();
	int32_t owningPlayer;
	auto OnCollide = [&](const GameObjectDef* otherObject) {
		std::cout << otherObject->position.x << std::endl;
		
		if (otherObject->position.x < 0.5f) {
			m_movementObject.movement.left = 0;
			m_movementObject.movement.right = 1;
		}
		else {
			m_movementObject.movement.left = 1;
			m_movementObject.movement.right = 0;
		}
		if (otherObject->position.y < 0.5f) {
			m_movementObject.movement.down = 0;
			m_movementObject.movement.up = 1;
		}
		else {
			m_movementObject.movement.down = 1;
			m_movementObject.movement.up = 0;
		}
		owningPlayer = otherObject->id;
	};
	OnCollideObserver obs(OnCollide, m_gameObject.id);
	PhysicsSubject.Attach(obs);
}
