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
		void Add(MovementDefinition* component);
		void Render(float dt);
		MovementDefinition* GetMovementDefinitionByParentID(uint64_t id);
		void Integrate(float dt, MovementDefinition* definition);
	private:
		GameInputHandler(void) {}
		GameInputHandler(GameInputHandler const&);
		void operator=(GameInputHandler const&);
		std::vector<MovementDefinition*> Objects;
	};
}


