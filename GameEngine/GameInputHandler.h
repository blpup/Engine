#pragma once
#include <GLFW/glfw3.h>
#include "Enums.h"
#include "MovementComponent.h"
#include <vector>

namespace GameEngine {
	class GameInputHandler
	{
	public:
		struct KeyConverter {
			Direction direction;
			int GLFWkey;
		};
		static GameInputHandler& GetInstance() {
			static GameInputHandler instance;
			return instance;
		}
		static void ButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			GetInstance().ButtonCallbackImpl(key, action);
		}
		void ButtonCallbackImpl(int key, int action);
		void Add(MovementDef* component);
		Direction GetUserInput();
		void Render();
	private:
		GameInputHandler(void) {}
		GameInputHandler(GameInputHandler const&);
		void operator=(GameInputHandler const&);
		std::vector<MovementDef*> Objects;
		Direction m_userInput;
	};
}


