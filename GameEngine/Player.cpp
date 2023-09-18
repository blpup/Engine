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
#include <memory>

using namespace GameEngine;
Player::Player()
{
	GameObject goWrapper(&m_gameObject);
	
	goWrapper.SetCoords(-0.9, 0);
	m_gameObject.position = goWrapper.GetCoords();
	m_renderObject.parentId = goWrapper.GetID();
	m_movementObject.parentId = goWrapper.GetID();
	m_physicsObject.parentId = goWrapper.GetID();
	m_physicsObject.physicsType = PhysicsType::WORLD;
	m_renderObject.color = Color3(1.f, 0.0f, 0.0f);
	m_renderObject.textureObject.fileLocation = const_cast<char*>("./mario.png");
	m_renderObject.vertices = BoxComponent(.1f, .1f).GetVertices();
	m_renderObject.verts = RenderComponent(&m_renderObject).GenerateVertices();
	m_physicsObject.height = .3f;
	m_physicsObject.width = .1f;
	m_movementObject.keybindings =
	{
		Keybindings(Direction::LEFT,GLFW_KEY_A),
		Keybindings(Direction::RIGHT,GLFW_KEY_D),
		Keybindings(Direction::UP,GLFW_KEY_SPACE)
	};
	Entity::registerComponent(goWrapper.GetID(), Entity::ComponentId::Player);

	goWrapper.instantiate(m_gameObject);
	PhysicsComponent(&m_physicsObject).instantiate(&m_physicsObject);
	RenderComponent(&m_renderObject).instantiate(&m_renderObject);
	MovementComponent(&m_movementObject).instantiate(&m_movementObject);
}

