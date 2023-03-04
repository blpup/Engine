#include "GameInputHandler.h"
#include "MovementComponent.h"
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
		for (size_t j = 0; j < Objects[i]->GetKeyBindings().size(); j++)
		{
			if (key == Objects[i]->GetKeyBindings()[j].GLFWkey && action == GLFW_PRESS) {
				Objects[i]->SetMovement(Objects[i]->GetKeyBindings()[j].direction, 1);
				m_userInput = Objects[i]->GetKeyBindings()[j].direction;
			}
			if (key == Objects[i]->GetKeyBindings()[j].GLFWkey && action == GLFW_RELEASE) {
				Objects[i]->SetMovement(Objects[i]->GetKeyBindings()[j].direction, 0);
			}
		}
	}

}

void GameInputHandler::AddMovementComponent(MovementComponent* component)
{
	Objects.push_back(component);
}

Direction GameInputHandler::GetUserInput()
{
	return m_userInput;
}

void GameInputHandler::Render()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Move();
	}
}
