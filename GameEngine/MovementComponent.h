#pragma once
#include "Vector2.h"
#include "Structs.h"
#include "Enums.h"
#include "UUID.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include <vector>
namespace GameEngine {
	struct Keybindings {
		Direction direction;
		int GLFWkey;
		Keybindings(Direction dir, int key)
			: direction(dir), GLFWkey(key) {}
	};
	struct MovementDef {
		MovementDef():
		speed(0.005f),parentId(0),movement(Movablitiy(0,0,0,0)) {}
		UUID id;
		uint64_t parentId;
		Movablitiy movement{0,0,0,0};
		std::vector<Keybindings> keybindings;
		float speed;
	};
	class MovementComponent
	{
	public:
		MovementComponent(const MovementDef* object);
		uint64_t getParentID();
		void SetMovement(Direction direction, int movement);
		Movablitiy GetMovement() const;
		std::vector<Keybindings> GetKeyBindings() const;
		void instantiate(MovementDef* object);
		void Move(GameObjectDef& object, Movablitiy physicsMovability);
		void SetSpeed(float value);
		float GetSpeed();
	private:
		Movablitiy m_movement;
		uint64_t m_parentID;
		float m_speed;
		std::vector<Keybindings> m_keybindings;
	};
}


