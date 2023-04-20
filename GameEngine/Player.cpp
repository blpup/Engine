#include "Player.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "BoxComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "Entity.h"
#include "Vector2.h"
#include <vector>

using namespace GameEngine;
Player::Player()
{
	GameObject goWrapper(&m_gameObject);

	goWrapper.SetCoords(-0.9, 0);
	m_gameObject.position = goWrapper.GetCoords();
	boxComponent = new BoxComponent(.05f, .5f);
	m_renderObject.parentId = goWrapper.GetID();
	m_movementObject.parentId = goWrapper.GetID();
	m_physicsObject.parentId = goWrapper.GetID();
	m_renderObject.color = Color3(0.f, 0.0f, 1.0f);
	m_renderObject.vertices = boxComponent->GetVertices();
	m_physicsObject.height = .5f;
	m_physicsObject.width = .05f;
	m_movementObject.keybindings =
	{
		Keybindings(Direction::UP,GLFW_KEY_W),
		Keybindings(Direction::DOWN,GLFW_KEY_S),
	};

	Entity::registerComponent(goWrapper.GetID(), Entity::ComponentId::Player);
	PhysicsComponent(&m_physicsObject).instantiate(&m_physicsObject);
	RenderComponent(&m_renderObject).instantiate(&m_renderObject);
	MovementComponent(&m_movementObject).instantiate(&m_movementObject);
}

