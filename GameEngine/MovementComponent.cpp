#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "GameObjectHandler.h"
#include "PhysicsComponent.h"
#include "GamePhysics.h"
#include "Entity.h"

using namespace GameEngine;

MovementComponent::MovementComponent(const MovementDefinition* object)
	:m_movement(object->movement), m_keybindings(object->keybindings), m_parentID(object->parentId), m_speed(object->speed), m_cosAngle(object->cosAngle), m_sinAngle(object->sinAngle), m_jump(object->jump)
{
}

uint64_t MovementComponent::getParentID()
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

void MovementComponent::instantiate(MovementDefinition* object)
{
	Entity::registerComponent(object->parentId, Entity::ComponentId::Movement);
	GameInputHandler::GetInstance().Add(object);
}

void MovementComponent::Move(GameObjectDefinition& object, Movablitiy physicsMovability)
{
	GameObject objWrapper(&object);
	PhysicsComponent phyWrapper(GamePhysics::GetInstance().GetPhysicsObjectByParentId(object.id));
	
	if (GetMovement().up == 1 && physicsMovability.up == 1) {
		CalculateUp(&phyWrapper, &objWrapper);
	}
	if (GetMovement().down == 1 && physicsMovability.down == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x, objWrapper.GetCoords().y - (GetSpeed() * sinf(GetSinAngle())));
	}
	if (phyWrapper.getPhysicsType() == PhysicsType::WORLD && physicsMovability.down == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x, objWrapper.GetCoords().y - (GRAVITY * sinf(GetSinAngle())));
	}
	if (GetMovement().left == 1 && physicsMovability.left == 1) {
		objWrapper.SetCoords((objWrapper.GetCoords().x - (GetSpeed() * cosf(GetCosAngle()))), objWrapper.GetCoords().y);
	}
	if (GetMovement().right == 1 && physicsMovability.right == 1) {
		objWrapper.SetCoords(objWrapper.GetCoords().x + (GetSpeed() * cosf(GetCosAngle())), objWrapper.GetCoords().y);
	}


	if (phyWrapper.getPhysicsType() == PhysicsType::WORLD) {
		MovementDefinition* temp = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(objWrapper.GetID());
		if (physicsMovability.down == 0) {
			temp->jump = Jump::CAN_JUMP;
		}
		if(physicsMovability.up == 1)
			objWrapper.SetCoords(objWrapper.GetCoords().x, objWrapper.GetCoords().y + (temp->velocity * GetSpeed() * sinf(GetSinAngle())));
	}
	//std::cout << GetSpeed() << std::endl;
	object.position.SetVector2(objWrapper.GetCoords());
}

void MovementComponent::SetSpeed(float value)
{
	m_speed = value;
}

float MovementComponent::GetSpeed()
{
	return m_speed;
}

void MovementComponent::CalculateUp(PhysicsComponent* pComponent, GameObject* gComponent)
{
	if (pComponent->getPhysicsType() == PhysicsType::STATIC) {
		gComponent->SetCoords(gComponent->GetCoords().x, gComponent->GetCoords().y + (GetSpeed() * sinf(GetSinAngle())));
		return;
	}

	if (pComponent->getPhysicsType() == PhysicsType::WORLD) {
		MovementDefinition* temp = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(gComponent->GetID());
		if (m_jump == Jump::CAN_JUMP) {
			temp->acceleration = 12;
			temp->jump = Jump::CANT_JUMP;
		}
		return;
	}
}
