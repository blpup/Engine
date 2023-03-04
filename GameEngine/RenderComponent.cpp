#include "RenderComponent.h"
#include "GameRenderer.h"
#include "GameObject.h"
using namespace GameEngine;

RenderComponent::RenderComponent(Vector2 position, Color3 color, std::vector<float> vertices, int zIndex, GLenum renderType, GameObject& object)
	:m_object(object)
{
	GameRenderer& RendererSystem = GameRenderer::GetInstance();
	m_RenderObject.m_color = color;
	m_RenderObject.m_position = position;
	m_RenderObject.m_zIndex = zIndex;
	m_RenderObject.m_vertices = vertices;
	m_RenderObject.m_renderType = renderType;
	m_RenderObject.m_ID = m_object.GetID();
	RendererSystem.Add(this);
}

RenderComponent::RenderObject RenderComponent::GetRenderObject() const
{
	return m_RenderObject;
}

GameObject& GameEngine::RenderComponent::GetAttachedObject() const
{
	return m_object;
}


