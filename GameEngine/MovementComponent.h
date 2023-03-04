#pragma once
#include "Vector2.h"
#include "Enums.h"
#include <vector>
namespace GameEngine {
	class MovementComponent
	{
	public:
		struct Movement {
			int forward = 0;
			int backward = 0;
			int left = 0;
			int right = 0;
		};
		struct Keybindings {
			Direction direction;
			int GLFWkey;
			Keybindings(Direction dir, int key)
				: direction(dir), GLFWkey(key){}
		};
		MovementComponent(class GameObject& object, struct std::vector<Keybindings> keybindings);
		void UpdatePosition(Vector2 coords);
		void SetMovement(Direction direction, int movement);
		Movement GetMovement() const;
		std::vector<Keybindings> GetKeyBindings() const;
		void Move();
	private:
		GameObject& m_currentObject;
		Movement m_movement;
		std::vector<Keybindings> m_keybindings;

		class PhysicsComponent* RegisteredPhysicsComponent = nullptr;
	};
}


