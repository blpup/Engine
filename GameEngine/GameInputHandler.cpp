#include "GameInputHandler.h"
#include "GameObjectHandler.h"
#include "PhysicsComponent.h"
#include "GamePhysics.h"
#include "GameObject.h"
#include <iostream>
using namespace GameEngine;
void GameInputHandler::ButtonCallbackImpl(int key, int action)
{
	if (Objects.empty()) {
		std::cout << "No Movement Component Set." << std::endl;
		return;
	}
	for (size_t i = 0; i < Objects.size(); i++)
	{
		MovementComponent movWrapper(Objects[i]);
		for (size_t j = 0; j < movWrapper.GetKeyBindings().size(); j++)
		{
			if (key == movWrapper.GetKeyBindings()[j].GLFWkey && action == GLFW_PRESS) {
				movWrapper.SetMovement(movWrapper.GetKeyBindings()[j].direction, 1);
				Objects[i]->movement = movWrapper.GetMovement();
				m_userInput = movWrapper.GetKeyBindings()[j].direction;
			}
			if (key == movWrapper.GetKeyBindings()[j].GLFWkey && action == GLFW_RELEASE) {
				movWrapper.SetMovement(movWrapper.GetKeyBindings()[j].direction, 0);
				Objects[i]->movement = movWrapper.GetMovement();
			}
		}
	}

}

void GameInputHandler::Add(MovementDef* component)
{
	Objects.push_back(component);
}

Direction GameInputHandler::GetUserInput()
{
	return m_userInput;
}

void GameInputHandler::Render()
{
	GamePhysics& PhysicsHandler =  GamePhysics::GetInstance();
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	
	for (size_t i = 0; i < Objects.size(); i++)
	{
		MovementComponent movWrapper(Objects[i]);
		const int objectIndex = ObjectHandler.GetGameObjectIndex(movWrapper.getParentID());
		PhysicsHandler.GetPhysicsObjectByParentId(movWrapper.getParentID())->move;
		if (objectIndex < 0) {
			continue;
		};
		GameObject GameObject(&ObjectHandler.GetGameObject(objectIndex));
		movWrapper.Move(ObjectHandler.GetGameObject(objectIndex), PhysicsHandler.GetPhysicsObjectByParentId(movWrapper.getParentID())->move);
		//GameObject.SetCoords()
	}
}
