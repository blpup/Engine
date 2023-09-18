#include "GameInputHandler.h"
#include "GameObjectHandler.h"
#include "PhysicsComponent.h"
#include "GamePhysics.h"
#include "GameObject.h"
#include <iostream>
using namespace GameEngine;
void GameInputHandler::ButtonCallbackImpl(int key, int action)
{
	if (Objects.empty())
		return;

	for (size_t i = 0; i < Objects.size(); i++)
	{
		MovementComponent movWrapper(Objects[i]);
		for (size_t j = 0; j < movWrapper.GetKeyBindings().size(); j++)
		{
			if (key == movWrapper.GetKeyBindings()[j].GLFWkey && action == GLFW_PRESS) {
				movWrapper.SetMovement(movWrapper.GetKeyBindings()[j].direction, 1);
				Objects[i]->movement = movWrapper.GetMovement();
			}
			if (key == movWrapper.GetKeyBindings()[j].GLFWkey && action == GLFW_RELEASE) {
				movWrapper.SetMovement(movWrapper.GetKeyBindings()[j].direction, 0);
				Objects[i]->movement = movWrapper.GetMovement();
			}
		}
	}

}

void GameInputHandler::Add(MovementDefinition* component)
{
	Objects.push_back(component);
}

void GameInputHandler::Render(float dt)
{
	GamePhysics& PhysicsHandler =  GamePhysics::GetInstance();
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	for (size_t i = 0; i < Objects.size(); i++)
	{
		MovementComponent movWrapper(Objects[i]);
		const int objectIndex = ObjectHandler.GetGameObjectIndex(movWrapper.getParentID());
		if (objectIndex < 0)
			continue;

		GameObject GameObject(&ObjectHandler.GetGameObject(objectIndex));


		Integrate(dt, Objects[i]);
		movWrapper.SetSpeed(movWrapper.GetSpeed() * dt);
		movWrapper.Move(ObjectHandler.GetGameObject(objectIndex), PhysicsHandler.GetPhysicsObjectByParentId(movWrapper.getParentID())->move);
	}
	
}

MovementDefinition* GameEngine::GameInputHandler::GetMovementDefinitionByParentID(uint64_t id)
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		if (MovementComponent(Objects[i]).getParentID() == id)
			return Objects[i];
	}
	return nullptr;
}

void GameEngine::GameInputHandler::Integrate(float dt, MovementDefinition* definition)
{
	if (definition->velocity < definition->acceleration) {
		definition->velocity += definition->speed;
		return;
	}
	if (definition->acceleration <= 0) {
		definition->velocity = 0;
		definition->acceleration = 0;
		return;
	}		
	definition->velocity -= definition->speed;
	definition->acceleration -= definition->speed;
}
