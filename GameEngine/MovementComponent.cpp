#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "GameObjectHandler.h"
#include "Entity.h"

using namespace GameEngine;

MovementComponent::MovementComponent(const MovementDef* object)
	:m_movement(object->movement), m_keybindings(object->keybindings), m_parentID(object->parentId), m_speed(object->speed)
{
}

uint64_t GameEngine::MovementComponent::getParentID()
{
	return m_parentID;
}

void MovementComponent::SetMovement(Direction direction, int movement)
{
	if (direction == Direction::UP) {
		m_movement.up = movement;
	}
	else if (direction == Direction::DOWN) {
		m_movement.down = movement;
	}
	else if (direction == Direction::LEFT) {
		m_movement.left = movement;
	}
	else if (direction == Direction::RIGHT) {
		m_movement.right = movement;
	}
}

Movablitiy MovementComponent::GetMovement() const
{
	return m_movement;
}

std::vector<Keybindings> MovementComponent::GetKeyBindings() const
{
	return m_keybindings;
}

void MovementComponent::instantiate(MovementDef* object)
{
	Entity::registerComponent(object->parentId, Entity::ComponentId::Movement);
	GameInputHandler::GetInstance().Add(object);
}

void MovementComponent::Move(GameObjectDef& object, Movablitiy physicsMovability)
{
	GameObject objWrapper(&object);
	if (GetMovement().up == 1 && physicsMovability.up == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x, objWrapper.GetCoords().y + GetSpeed());
	}
	if (GetMovement().down == 1 && physicsMovability.down == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x, objWrapper.GetCoords().y - GetSpeed());
	}
	if (GetMovement().left == 1 && physicsMovability.left == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x - GetSpeed(), objWrapper.GetCoords().y);
	}
	if (GetMovement().right == 1 && physicsMovability.right ==1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x + GetSpeed(), objWrapper.GetCoords().y);
	}
	object.position.SetVector2(objWrapper.GetCoords());
}

void GameEngine::MovementComponent::SetSpeed(float value)
{
	m_speed = value;
}

float GameEngine::MovementComponent::GetSpeed()
{
	return m_speed;
}
