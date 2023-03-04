#include "GamePhysics.h"
#include "PhysicsComponent.h"
#include "GameInputHandler.h"
#include "Vector2.h"
#include "GameObject.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace GameEngine;
GamePhysics& GamePhysics::GetInstance()
{
	static GamePhysics instance;
	return instance;
}
void GamePhysics::Add(PhysicsComponent* component)
{
	Objects.push_back(component);
}

void GamePhysics::Remove(PhysicsComponent* component)
{
}

void GamePhysics::Render()
{
	GameInputHandler& InputHandle = GameInputHandler::GetInstance();
	for (size_t i = 0; i < Objects.size(); i++)
	{
		PhysicsObject& PhysicsObject1 = Objects[i]->GetPhysicsObject();
		if (PhysicsObject1.m_collision != Collision::CAN_COLLIDE)
			continue;

		UpdateMovability(&PhysicsObject1, Direction::RESET);
		for (size_t j = 0; j < Objects.size(); j++)
		{
			PhysicsObject& PhysicsObject2 = Objects[j]->GetPhysicsObject();
			if (Objects[j]->GetID() == Objects[i]->GetID())
				continue;
			if (PhysicsObject2.m_collision != Collision::CAN_COLLIDE)
				continue;
			UpdateMovability(&PhysicsObject2, Direction::RESET);
			float deltaX = abs(Objects[i]->GetObject().GetCoords().x - Objects[j]->GetObject().GetCoords().x);
			float deltaY = abs(Objects[i]->GetObject().GetCoords().y - Objects[j]->GetObject().GetCoords().y);

			if (CheckCollision(deltaX, deltaY, PhysicsObject1.m_width, PhysicsObject1.m_height, PhysicsObject2.m_width, PhysicsObject2.m_height)) {
					UpdateMovability(&PhysicsObject1, CollisionDirection(*Objects[i], *Objects[j]));
					UpdateMovability(&PhysicsObject2, CollisionDirection(*Objects[j], *Objects[i]));
						
			}
			else {
				b_nextStepCollisionTriggered = false;
			}

			if (!b_nextStepCollisionTriggered) {
				CalculateNextStep(*Objects[i], *Objects[j]);
			}
		}
	}
}

PhysicsComponent* GamePhysics::GetPhysicsComponentByID(int id)
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->GetID() == id) {
			return Objects[i];
		}
	}
	return nullptr;
}

//This is an AABB collision checker. Since all of our collisions are box collisions this is the easiest way to check if two objects are colliding.
int GamePhysics::CheckCollision(float deltaX, float deltaY, float width1, float height1, float width2, float heigth2) const
{
	float intersectX = deltaX - ((width1 / 2) + (width2 / 2));
	float intersectY = deltaY - ((height1 / 2) + (heigth2 / 2));
	if (intersectX < 0.0f && intersectY < 0.0f) {
		return 1;
	}
	return 0;
}

Direction GamePhysics::CollisionDirection(PhysicsComponent& object, PhysicsComponent& other) const
{
	float right = abs((object.GetObject().GetCoords().x + object.GetPhysicsObject().m_width/2) - (other.GetObject().GetCoords().x - other.GetPhysicsObject().m_width/2));
	float left = abs((object.GetObject().GetCoords().x - object.GetPhysicsObject().m_width/2) - (other.GetObject().GetCoords().x + other.GetPhysicsObject().m_width / 2));
	float top = abs((object.GetObject().GetCoords().y + object.GetPhysicsObject().m_height/2) - (other.GetObject().GetCoords().y - other.GetPhysicsObject().m_height / 2));
	float bottom = abs((object.GetObject().GetCoords().y - object.GetPhysicsObject().m_height/2) - (other.GetObject().GetCoords().y + other.GetPhysicsObject().m_height / 2));
	float min = std::min({ right, left, top, bottom });
	if (min == right) {
		return Direction::RIGHT;
	}
	else if (min == left) {
		return Direction::LEFT;
	}
	else if (min == top) {
		return Direction::UP;
	}
	else if (min == bottom) {
		return Direction::DOWN;
	}
	return Direction::RESET;
}

void GamePhysics::UpdateMovability(struct PhysicsObject* object, Direction direction)
{
	switch (int(direction))
	{
	case 2:
		object->m_move.backward = 0;
		break;
	case 3:
		object->m_move.left = 0;
		break;
	case 0:
		object->m_move.forward = 0;
		break;
	case 1:
		object->m_move.right = 0;
		break;
	default:
		object->m_move.backward = 1;
		object->m_move.left = 1;
		object->m_move.forward = 1;
		object->m_move.right = 1;
		break;
	}
}

float GamePhysics::Bisection(PhysicsComponent& PComponent1, PhysicsComponent& PComponent2, float speed)
{
	float deltaX = PComponent1.GetObject().GetCoords().x - PComponent2.GetObject().GetCoords().x;
	float deltaY = PComponent1.GetObject().GetCoords().y - PComponent2.GetObject().GetCoords().y;
	float p1Width = PComponent1.GetPhysicsObject().m_width;
	float p1Height = PComponent1.GetPhysicsObject().m_height;
	float p2Width = PComponent2.GetPhysicsObject().m_width;
	float p2Height = PComponent2.GetPhysicsObject().m_height;

	if (CheckCollision(abs(deltaX) - speed, abs(deltaY) - speed, p1Width, p1Height, p2Width, p2Height)) return speed;
	Bisection(PComponent1, PComponent2, (speed + 0.01f) / 2);
	b_nextStepCollisionTriggered = true;
	
}

void GamePhysics::CalculateNextStep(PhysicsComponent& PComponent1, PhysicsComponent& PComponent2)
{
	float deltaX = PComponent1.GetObject().GetCoords().x - PComponent2.GetObject().GetCoords().x;
	float deltaY = PComponent1.GetObject().GetCoords().y - PComponent2.GetObject().GetCoords().y;
	float p1Width = PComponent1.GetPhysicsObject().m_width;
	float p1Height = PComponent1.GetPhysicsObject().m_height;
	float p2Width = PComponent2.GetPhysicsObject().m_width;
	float p2Height = PComponent2.GetPhysicsObject().m_height;

	if (!CheckCollision(abs(deltaX) - 0.01f, abs(deltaY) - 0.01f, p1Width, p1Height, p2Width, p2Height)) return;
	float distance = Bisection(PComponent1, PComponent2, 0);
	GameInputHandler& InputHandle = GameInputHandler::GetInstance();
	PComponent1.GetObject().SetSpeed(distance);
	PComponent2.GetObject().SetSpeed(distance);
}
