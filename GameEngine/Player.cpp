#include "Player.h"
#include "GamePhysics.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include <vector>

using namespace GameEngine;
Player::Player()
{
	GameObject goWrapper(&m_gameObject);
	RenderComponent renWrapper(&m_renderObject);
	MovementComponent movWrapper(&m_movementObject);
	PhysicsComponent phyWrapper(&m_physicsObject);
	m_gameObject.position.SetVector2(0.2f, 0.2f);
	circleComponent = new CircleComponent(.05f, goWrapper.GetCoords());
	m_renderObject.parentId = m_gameObject.id;
	m_movementObject.parentId = m_gameObject.id;
	m_physicsObject.parentId = m_gameObject.id;
	m_renderObject.color = Color3(0.f, 1.0f, 1.0f);
	m_renderObject.vertices = circleComponent->GetVertices();
	m_movementObject.keybindings =
	{ 
		Keybindings(Direction::UP,GLFW_KEY_W),
		Keybindings(Direction::DOWN,GLFW_KEY_S),
		Keybindings(Direction::LEFT,GLFW_KEY_A),
		Keybindings(Direction::RIGHT,GLFW_KEY_D)
	};
	renWrapper.instantiate(&m_renderObject);
	movWrapper.instantiate(&m_movementObject);
	phyWrapper.instantiate(&m_physicsObject);
}

