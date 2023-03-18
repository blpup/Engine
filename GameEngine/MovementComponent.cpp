#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "GameObjectHandler.h"

using namespace GameEngine;

MovementComponent::MovementComponent(const MovementDef* object)
	:m_movement(object->movement), m_keybindings(object->keybindings), m_parentID(object->parentId)
{
}

void MovementComponent::UpdatePosition(Vector2 coords)
{
	//m_currentObject.SetCoords(coords.x, coords.y);
}

uint64_t GameEngine::MovementComponent::getParentID()
{
	return m_parentID;
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

Movement MovementComponent::GetMovement() const
{
	return m_movement;
}

std::vector<Keybindings> MovementComponent::GetKeyBindings() const
{
	return m_keybindings;
}

void GameEngine::MovementComponent::instantiate(MovementDef* object)
{
	GameInputHandler::GetInstance().Add(object);
}

void MovementComponent::Move(GameObjectDef& object, Movablitiy physicsMovability)
{
	//GameObject gameObject(&ObjectHandler.GetGameObject())
	//if (RegisteredPhysicsComponent == nullptr) {
	//	GamePhysics& PhysicsSystem = GamePhysics::GetInstance();
		//RegisteredPhysicsComponent = PhysicsSystem.GetPhysicsComponentByID(m_currentObject.GetID());
	//}
	if (GetMovement().forward == 1 && physicsMovability.forward == 1) {
		object.position.SetVector2(object.position.x, object.position.y + 0.005f);
	}
	if (GetMovement().backward == 1 && physicsMovability.backward == 1) {
		object.position.SetVector2(object.position.x, object.position.y - 0.005f);
	}
	if (GetMovement().left == 1 && physicsMovability.left == 1) {
		object.position.SetVector2(object.position.x - .005f, object.position.y);
	}
	if (GetMovement().right == 1 && physicsMovability.right ==1) {
		object.position.SetVector2(object.position.x + .005f, object.position.y);
	}
	//RegisteredPhysicsComponent->CanMove().right == 1
}
