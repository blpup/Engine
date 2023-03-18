#include "GameObject.h"
#include <iostream>

using namespace GameEngine;
GameObject::GameObject(const GameObjectDef* object):
	m_id(object->id),m_position(object->position)
{

}

GameObject::GameObject(const GameObjectDef* object, uint64_t id):
	m_id(id), m_position(object->position)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Destroy()
{
}

Vector2 GameObject::GetCoords() const
{
	return m_position;
}

void GameObject::SetCoords(float x, float y)
{
	m_position.SetVector2(x, y);
}

uint64_t GameObject::GetID() const
{
	return m_id;
}

void GameObject::OnCollide(GameObject* OtherObject, int direction)
{
	//std::cout << m_ID << std::endl;
}
