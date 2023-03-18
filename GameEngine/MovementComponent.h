#pragma once
#include "Vector2.h"
#include "Enums.h"
#include "UUID.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include <vector>
namespace GameEngine {
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
			: direction(dir), GLFWkey(key) {}
	};
	struct MovementDef {
		UUID id;
		uint64_t parentId;
		Movement movement;
		std::vector<Keybindings> keybindings;
	};
	class MovementComponent
	{
	public:
		MovementComponent(const MovementDef* object);
		void UpdatePosition(Vector2 coords);
		uint64_t getParentID();
		void SetMovement(Direction direction, int movement);
		Movement GetMovement() const;
		std::vector<Keybindings> GetKeyBindings() const;
		void instantiate(MovementDef* object);
		void Move(GameObjectDef& object, Movablitiy physicsMovability);
	private:
		Movement m_movement;
		uint64_t m_parentID;
		std::vector<Keybindings> m_keybindings;
	};
}


