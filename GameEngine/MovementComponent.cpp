#include "MovementComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
using namespace GameEngine;

MovementComponent::MovementComponent(GameObject& object, std::vector<Keybindings> keybindings)
	:m_currentObject(object), m_keybindings(keybindings)
{
}

void MovementComponent::UpdatePosition(Vector2 coords)
{
	m_currentObject.SetCoords(coords.x, coords.y);
}

void MovementComponent::SetMovement(Direction direction, int movement)
{
	if (direction == Direction::UP) {
		m_movement.forward = movement;
	}
	else if (direction == Direction::DOWN) {
		m_movement.backward = movement;
	}
	else if (direction == Direction::LEFT) {
		m_movement.left = movement;
	}
	else if (direction == Direction::RIGHT) {
		m_movement.right = movement;
	}
}

MovementComponent::Movement MovementComponent::GetMovement() const
{
	return m_movement;
}

std::vector<MovementComponent::Keybindings> MovementComponent::GetKeyBindings() const
{
	return m_keybindings;
}

void MovementComponent::Move()
{
	if (RegisteredPhysicsComponent == nullptr) {
		GamePhysics& PhysicsSystem = GamePhysics::GetInstance();
		RegisteredPhysicsComponent = PhysicsSystem.GetPhysicsComponentByID(m_currentObject.GetID());
	}
	if (GetMovement().forward == 1 && RegisteredPhysicsComponent->CanMove().forward == 1) {
		UpdatePosition(Vector2(m_currentObject.GetCoords().x, m_currentObject.GetCoords().y + m_currentObject.GetSpeed()));
	}
	if (GetMovement().backward == 1 && RegisteredPhysicsComponent->CanMove().backward == 1) {
		UpdatePosition(Vector2(m_currentObject.GetCoords().x, m_currentObject.GetCoords().y - m_currentObject.GetSpeed()));
	}
	if (GetMovement().left == 1 && RegisteredPhysicsComponent->CanMove().left == 1) {
		UpdatePosition(Vector2(m_currentObject.GetCoords().x - m_currentObject.GetSpeed(), m_currentObject.GetCoords().y));
	}
	if (GetMovement().right == 1 && RegisteredPhysicsComponent->CanMove().right == 1) {
		UpdatePosition(Vector2(m_currentObject.GetCoords().x + m_currentObject.GetSpeed(), m_currentObject.GetCoords().y));
	}
}
