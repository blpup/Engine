#pragma once
#include "Vector2.h"
#include "Structs.h"
#include "Enums.h"
#include "UUID.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include <vector>
namespace GameEngine {
	enum class Jump {
		CAN_JUMP,
		CANT_JUMP
	};
	struct Keybindings {
		Direction direction;
		int GLFWkey;
		Keybindings(Direction dir, int key)
			: direction(dir), GLFWkey(key) {}
	};
	struct MovementDefinition {
		UUID id;
		uint64_t parentId = 0;
		Movablitiy movement{0,0,0,0};
		std::vector<Keybindings> keybindings;
		Jump jump = Jump::CAN_JUMP;
		float speed = 1.f;
		float maxSpeed = 1.f;
		float sinAngle = 90.0f;
		float cosAngle = 0.0f;
		float velocity = 0.0f;
		float acceleration = 0.0f;
	};

	class MovementComponent
	{
	public:
		MovementComponent(const MovementDefinition* object);
		uint64_t getParentID();
		void SetMovement(Direction direction, int movement);
		Movablitiy GetMovement() const;
		std::vector<Keybindings> GetKeyBindings() const;
		void instantiate(MovementDefinition* object);
		void Move(GameObjectDefinition& object, Movablitiy physicsMovability);
		void SetSpeed(float value);
		float GetSpeed();
		void SetSinAngle(float value) { m_sinAngle = value; };
		void SetCosAngle(float value) { m_cosAngle = value; }
		float GetSinAngle() { return m_sinAngle; };
		float GetCosAngle() { return m_cosAngle; };
		void CalculateUp(class PhysicsComponent* pComponent, class GameObject* gComponent);
	private:
		Movablitiy m_movement;
		uint64_t m_parentID;
		Jump m_jump;
		float m_speed;
		float m_sinAngle;
		float m_cosAngle;
		std::vector<Keybindings> m_keybindings;
	};
}


