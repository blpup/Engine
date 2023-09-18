#include "PhysicsComponent.h"
#include "GameObject.h"
#include "BoxComponent.h"
#include "vector2.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "GamePhysics.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include <random>

using namespace GameEngine;

PhysicsComponent::PhysicsComponent(const PhysicsObject* object)
	: m_collision(object->collision), m_collisionType(object->collisionType),
	m_width(object->width), m_height(object->height), m_move(object->move),
	m_id(object->id), m_parentId(object->parentId), m_physicsType(object->physicsType)
{}
PhysicsComponent::PhysicsComponent(const PhysicsObject* object, uint64_t id)
	: m_collision(object->collision), m_collisionType(object->collisionType),
	m_width(object->width), m_height(object->height), m_move(object->move),
	m_id(id), m_physicsType(object->physicsType)
{}
const Collision PhysicsComponent::getCollision() const {
	return m_collision;
}

void PhysicsComponent::setCollision(Collision value)
{
	m_collision = value;
}

const CollisionType PhysicsComponent::getCollisionType() const
{
	return m_collisionType;
}

void PhysicsComponent::setCollisionType(CollisionType value)
{
	m_collisionType = value;
}

const Movablitiy PhysicsComponent::getMovablitiy() const
{
	return m_move;
}

void PhysicsComponent::setMovablitiy(Movablitiy value)
{
	m_move = value;
}

const float PhysicsComponent::getHeight() const
{
	return m_height;
}

void PhysicsComponent::setHeight(float value)
{
	m_height = value;
}

const float PhysicsComponent::getWidth() const
{
	return m_width;
}

void PhysicsComponent::setWidth(float value)
{
	m_width = value;
}

const float PhysicsComponent::getVelocity() const
{
	return m_velocity;
}

void PhysicsComponent::setVelocity(float value)
{
	m_velocity = value;
}

uint64_t PhysicsComponent::getID() const {
	return m_id;
}
void PhysicsComponent::instantiate(PhysicsObject* object) {
	Entity::registerComponent(object->parentId, Entity::ComponentId::Physics);
	GamePhysics::GetInstance().Add(*object);
}
uint64_t PhysicsComponent::getParentID() const
{
	return m_parentId;
}

void PhysicsComponent::setPhysicsType(PhysicsType value)
{
	m_physicsType = value;
}

const PhysicsType PhysicsComponent::getPhysicsType()
{
	return m_physicsType;
}




