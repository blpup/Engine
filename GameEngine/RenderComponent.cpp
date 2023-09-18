#include "RenderComponent.h"
#include "GameRenderer.h"
#include "GameObject.h"
#include "Entity.h"

using namespace GameEngine;

RenderComponent::RenderComponent(const RenderObject* object):
	m_color(object->color), m_renderType(object->renderType), m_vertices(object->vertices), m_zIndex(object->zIndex),
	m_parentId(object->parentId),m_id(object->id), m_verts(object->verts)
{}
std::vector<Vertex> RenderComponent::GenerateVertices() {
	const float count = m_vertices.size() / 2;
	unsigned int iCounter = 0;
	for (size_t i = 0; i < count; i++)
	{
		Vertex vert;
		vert.position[0] = m_vertices[iCounter];
		vert.position[1] = m_vertices[iCounter + 1];
		vert.position[2] = 1;
		vert.color[0] = m_color.r;
		vert.color[1] = m_color.g;
		vert.color[2] = m_color.b;
		m_verts.push_back(vert);
		iCounter += 2;
	}
	return m_verts;
}
void GameEngine::RenderComponent::instantiate(RenderObject* object)
{
	Entity::registerComponent(object->parentId, Entity::ComponentId::Render);
	GameRenderer::GetInstance().Add(object);
}



