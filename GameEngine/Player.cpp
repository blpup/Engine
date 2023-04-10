#include "Player.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "BoxComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "Vector2.h"
#include <vector>

using namespace GameEngine;
Player::Player()
{
	GameObject goWrapper(&m_gameObject);
	RenderComponent renWrapper(&m_renderObject);
	MovementComponent movWrapper(&m_movementObject);
	PhysicsComponent phyWrapper(&m_physicsObject);
	goWrapper.SetCoords(-0.9, 0);
	m_gameObject.position = goWrapper.GetCoords();
	boxComponent = new BoxComponent(.05f, .5f);
	m_renderObject.parentId = m_gameObject.id;
	m_movementObject.parentId = m_gameObject.id;
	m_physicsObject.parentId = m_gameObject.id;
	m_renderObject.color = Color3(0.f, 0.0f, 1.0f);
	m_renderObject.vertices = boxComponent->GetVertices();
	m_physicsObject.height = .5f;
	m_physicsObject.width = .05f;
	m_movementObject.keybindings =
	{
		Keybindings(Direction::UP,GLFW_KEY_I),
		Keybindings(Direction::DOWN,GLFW_KEY_K),
	};
	phyWrapper.instantiate(&m_physicsObject);
	renWrapper.instantiate(&m_renderObject);
	movWrapper.instantiate(&m_movementObject);
	
}

