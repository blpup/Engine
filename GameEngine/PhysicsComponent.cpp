#include "PhysicsComponent.h"
#include "GameObject.h"
#include "BoxComponent.h"
#include "vector2.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include <vector>
#include <iostream>
#include <random>
#include "GamePhysics.h"
using namespace GameEngine;


PhysicsComponent::PhysicsComponent(Collision collision, CollisionType type, float width, float height, GameObject& object)
	: m_object(object), m_ID(object.GetID())
{
	GamePhysics& PhysicsSystem = GamePhysics::GetInstance();
	m_physicsObject.m_collision = collision;
	m_physicsObject.m_type = type;
	m_physicsObject.m_width = width;
	m_physicsObject.m_height = height;
	
	
#if DEBUG_PHYSICS_COLLISION == 1
	//For Physics debugging purposes to see the physics box rendered
	Color3 color((float)rand()/(float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	BoxComponent* box = new BoxComponent(m_physicsObject.m_width,m_physicsObject.m_height);
	RenderComponent* m_renderComponent = new RenderComponent(m_object.GetCoords(), color, box->GetVertices(), 2, GL_QUADS, m_object);
#endif

	PhysicsSystem.Add(this);
}

PhysicsObject& PhysicsComponent::GetPhysicsObject()
{
	return m_physicsObject;
}

void PhysicsComponent::UpdateCollision(Collision collision)
{
	m_physicsObject.m_collision = collision;
}

GameObject& GameEngine::PhysicsComponent::GetObject()
{
	return m_object;
}

Movablitiy PhysicsComponent::CanMove()
{
	return m_physicsObject.m_move;
}

int GameEngine::PhysicsComponent::GetID()
{
	return m_ID;
}

