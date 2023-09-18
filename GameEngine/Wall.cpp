#include "Wall.h"
#include "RenderComponent.h"
#include "BoxComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "Vector2.h"
#include <vector>
#include <memory>

using namespace GameEngine;
Wall::Wall()
{
	boxComponent = std::unique_ptr<BoxComponent>(new BoxComponent(4.0f, .02f));
	m_physicsObject.height = .02f;
	m_physicsObject.width = 4.0f;
	init();
}

GameEngine::Wall::Wall(float w, float h)
{
	boxComponent = std::unique_ptr<BoxComponent>(new BoxComponent(w, h));
	m_physicsObject.height = h;
	m_physicsObject.width = w;
	init();
}

void GameEngine::Wall::init()
{
	GameObject goWrapper(&m_gameObject);
	
	goWrapper.SetCoords(0, -1);
	m_gameObject.position = goWrapper.GetCoords();
	
	m_renderObject.parentId = m_gameObject.id;
	m_movementObject.parentId = m_gameObject.id;
	m_physicsObject.parentId = m_gameObject.id;
	m_renderObject.vertices = boxComponent->GetVertices();
	m_renderObject.color = Color3(0, 1, 0);
	m_renderObject.verts = RenderComponent(&m_renderObject).GenerateVertices();
	m_renderObject.textureObject.fileLocation = const_cast<char*>("./bricks.png");
	goWrapper.instantiate(m_gameObject);
	RenderComponent(&m_renderObject).instantiate(&m_renderObject);
	MovementComponent(&m_movementObject).instantiate(&m_movementObject);
	PhysicsComponent(&m_physicsObject).instantiate(&m_physicsObject);
}
