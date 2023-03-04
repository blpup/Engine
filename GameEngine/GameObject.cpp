#include "GameObject.h"
#include "GameObjectHandler.h"
#include <iostream>

using namespace GameEngine;
GameObject::GameObject():
	m_speed(0.f)
{
	m_coords.SetVector2(0, 0);
	std::cout << m_ID << std::endl;

	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	ObjectHandler.Add(this);
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
	return m_coords;
}

void GameObject::SetCoords(float x, float y)
{
	m_coords.SetVector2(x, y);
}

int GameObject::GetID() const
{
	return m_ID;
}


void GameObject::SetSpeed(float speed)
{
	m_speed = speed;
}

float GameObject::GetSpeed()
{
	return m_speed;
}

void GameObject::OnCollide(GameObject* OtherObject, int direction)
{
	//std::cout << m_ID << std::endl;
}
