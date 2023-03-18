#include "Wall.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "BoxComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "Vector2.h"
#include <vector>

using namespace GameEngine;
Wall::Wall()
{
	GameObject goWrapper(&m_gameObject);
	RenderComponent renWrapper(&m_renderObject);
	MovementComponent movWrapper(&m_movementObject);
	PhysicsComponent phyWrapper(&m_physicsObject);
	boxComponent = new BoxComponent(1.f, .1f);
	m_renderObject.parentId = m_gameObject.id;
	m_movementObject.parentId = m_gameObject.id;
	m_physicsObject.parentId = m_gameObject.id;
	m_renderObject.color = Color3(0.f, 0.0f, 1.0f);
	m_renderObject.vertices = boxComponent->GetVertices();
	m_physicsObject.height = 0.1f;
	m_physicsObject.width = 1.0f;
	m_movementObject.keybindings =
	{
		Keybindings(Direction::UP,GLFW_KEY_I),
		Keybindings(Direction::DOWN,GLFW_KEY_K),
		Keybindings(Direction::LEFT,GLFW_KEY_J),
		Keybindings(Direction::RIGHT,GLFW_KEY_L)
	};
	renWrapper.instantiate(&m_renderObject);
	movWrapper.instantiate(&m_movementObject);
	phyWrapper.instantiate(&m_physicsObject);
}
