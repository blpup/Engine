#include "RenderComponent.h"
#include "GameRenderer.h"
#include "GameObject.h"

using namespace GameEngine;



RenderComponent::RenderComponent(const RenderObject* object):
	m_color(object->color), m_renderType(object->renderType), m_vertices(object->vertices), m_zIndex(object->zIndex),
	m_parentId(object->parentId),m_id(object->id)
{
}

RenderComponent::RenderComponent(const RenderObject* object, uint64_t id):
	m_color(object->color), m_renderType(object->renderType),
	m_vertices(object->vertices), m_zIndex(object->zIndex), m_parentId(id)
{
}

uint64_t RenderComponent::getID()
{
	return m_id;
}

Color3 RenderComponent::getColor()
{
	return m_color;
}
uint64_t GameEngine::RenderComponent::getParentID()
{
	return m_parentId;
}
void GameEngine::RenderComponent::setParentID(uint64_t value)
{
	m_parentId = value;
	
}
void RenderComponent::setColor(Color3 value)
{
	m_color = value;
}
std::vector<float> RenderComponent::getVertices()
{
	return m_vertices;
}

void RenderComponent::setVertices(std::vector<float> value)
{
	m_vertices = value;
}

int RenderComponent::getZIndex()
{
	return m_zIndex;
}

void RenderComponent::setZIndex(int value)
{
	m_zIndex = value;
}
GLenum RenderComponent::getRenderType()
{
	return m_renderType;
}

void RenderComponent::setRenderType(GLenum value)
{
	m_renderType = value;
}

void GameEngine::RenderComponent::instantiate(RenderObject* object)
{
	GameRenderer::GetInstance().Add(object);
}



