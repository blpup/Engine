#include "PhysicsComponent.h"
#include "GameObject.h"
#include "BoxComponent.h"
#include "vector2.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "GamePhysics.h"
#include <vector>
#include <iostream>
#include <random>

using namespace GameEngine;


PhysicsComponent::PhysicsComponent(const PhysicsObject* object)
	: m_collision(object->collision), m_collisionType(object->collisionType),
	m_width(object->width), m_height(object->height), m_velocity(object->velocity), m_move(object->move),
	m_id(object->id), m_parentId(object->parentId)
{}
PhysicsComponent::PhysicsComponent(const PhysicsObject* object, uint64_t id)
	: m_collision(object->collision), m_collisionType(object->collisionType),
	m_width(object->width), m_height(object->height), m_velocity(object->velocity), m_move(object->move),
	m_id(id)
{}
Collision PhysicsComponent::getCollision() {
	return m_collision;
}

void PhysicsComponent::setCollision(Collision value)
{
	m_collision = value;
}

CollisionType PhysicsComponent::getCollisionType()
{
	return m_collisionType;
}

void PhysicsComponent::setCollisionType(CollisionType value)
{
	m_collisionType = value;
}

Movablitiy PhysicsComponent::getMovablitiy()
{
	return m_move;
}

void PhysicsComponent::setMovablitiy(Movablitiy value)
{
	m_move = value;
}

float PhysicsComponent::getHeight()
{
	return m_height;
}

void PhysicsComponent::setHeight(float value)
{
	m_height = value;
}

float PhysicsComponent::getWidth()
{
	return m_width;
}

void PhysicsComponent::setWidth(float value)
{
	m_width = value;
}

float PhysicsComponent::getVelocity()
{
	return m_velocity;
}

void PhysicsComponent::setVelocity(float value)
{
	m_velocity = value;
}
uint64_t PhysicsComponent::getID() {
	return m_id;
}
void PhysicsComponent::instantiate(PhysicsObject* object) {
	GamePhysics::GetInstance().Add(object);
}
uint64_t GameEngine::PhysicsComponent::getParentID()
{
	return m_parentId;
}




