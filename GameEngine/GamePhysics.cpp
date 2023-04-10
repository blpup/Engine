#include "GameInputHandler.h"
#include "Vector2.h"
#include "GameObject.h"
#include "GameObjectHandler.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Observer.h"

using namespace GameEngine;
GamePhysics& GamePhysics::GetInstance()
{
	static GamePhysics instance;
	return instance;
}
void GamePhysics::Add(PhysicsObject component)
{
	Objects.push_back(component);
}

void GamePhysics::Remove(PhysicsObject* component)
{
}

void GamePhysics::Render()
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		m_currentObject = &Objects[i];
		PhysicsComponent PhysicsObject1(m_currentObject);
		if (PhysicsObject1.getCollision() != Collision::CAN_COLLIDE)
			continue;

		for (size_t j = 0; j < Objects.size(); j++)
		{
			m_targetObject = &Objects[j];
			PhysicsComponent PhysicsObject2(m_targetObject);

			if (PhysicsObject1.getID() == PhysicsObject2.getID())
				continue;
			if (PhysicsObject2.getCollision() != Collision::CAN_COLLIDE)
				continue;
			
			Vector2 deltas = CalculateDeltas();
			
			if (CheckCollision(deltas.x, deltas.y)) {
				DoCollisionSteps();
			}
			else {
				b_nextStepCollisionTriggered = false;
			}

			if (!b_nextStepCollisionTriggered) {
				CalculateNextStep();
			}
		}
	}
}

size_t GamePhysics::GetPhysicsComponentIndex(int id)
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		if (PhysicsComponent(&Objects[i]).getID() == id)
			return i;
	}
	return -1;
}

PhysicsObject* GamePhysics::GetPhysicsObjectByParentId(uint64_t id)
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		if (PhysicsComponent(&Objects[i]).getParentID() == id)
			return &Objects[i];
	}
	return nullptr;
}

//This is an AABB collision checker. Since all of our collisions are box collisions this is the easiest way to check if two objects are colliding.
int GamePhysics::CheckCollision(float deltaX, float deltaY) const
{
	PhysicsComponent PhysicsObject1(m_currentObject);
	PhysicsComponent PhysicsObject2(m_targetObject);
	float intersectX = deltaX - ((PhysicsObject1.getWidth() / 2) + (PhysicsObject2.getWidth() / 2));
	float intersectY = deltaY - ((PhysicsObject1.getHeight() / 2) + (PhysicsObject2.getHeight() / 2));
	if (intersectX < 0.0f && intersectY < 0.0f) {
		return 1;
	}
	return 0;
}

void GameEngine::GamePhysics::DoCollisionSteps()
{
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	PhysicsComponent PhysicsObject1(m_currentObject);

	UpdateMovability(*m_currentObject, CollisionDirection(m_currentObject, m_targetObject));
	UpdateMovability(*m_targetObject, CollisionDirection(m_targetObject, m_currentObject));

	//Mock Event call. These eventuall needs to be replaced with a proper event handling system.
	PhysicsSubject& PhysicsSubject = PhysicsSubject::GetInstance();
	PhysicsSubject.Notify(ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject1.getParentID())));
}

Vector2 GamePhysics::CalculateDeltas()
{
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	PhysicsComponent PhysicsObject1(m_currentObject);
	PhysicsComponent PhysicsObject2(m_targetObject);
	GameObject GameObject1(&ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject1.getParentID())));
	GameObject GameObject2(&ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject2.getParentID())));
	Vector2 diff = GameObject1.GetCoords() - GameObject2.GetCoords();
	return Vector2(abs(diff.x), abs(diff.y));
}

Direction GamePhysics::CollisionDirection(PhysicsObject* o1, PhysicsObject* o2) const
{
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	PhysicsComponent PhysicsObject1(o1);
	PhysicsComponent PhysicsObject2(o2);
	GameObject GameObject1(&ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject1.getParentID())));
	GameObject GameObject2(&ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject2.getParentID())));

	float right = abs((GameObject1.GetCoords().x + PhysicsObject1.getWidth() / 2) - (GameObject2.GetCoords().x - PhysicsObject2.getWidth() / 2));
	float left = abs((GameObject1.GetCoords().x - PhysicsObject1.getWidth() /2) - (GameObject2.GetCoords().x + PhysicsObject2.getWidth() / 2));
	float top = abs((GameObject1.GetCoords().y + PhysicsObject1.getHeight() / 2) - (GameObject2.GetCoords().y - PhysicsObject2.getHeight() / 2));
	float bottom = abs((GameObject1.GetCoords().y - PhysicsObject1.getHeight() /2) - (GameObject2.GetCoords().y + PhysicsObject2.getHeight() / 2));
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

void GamePhysics::UpdateMovability(struct PhysicsObject& object, Direction direction)
{
	PhysicsComponent phyWrapper(&object);
	switch (int(direction))
	{
	case 2:
		phyWrapper.setMovablitiy(Movablitiy(1, 0, 1, 1));
		object.move = phyWrapper.getMovablitiy();
		break;
	case 3:
		phyWrapper.setMovablitiy(Movablitiy(1, 1, 0, 1));
		object.move = phyWrapper.getMovablitiy();
		break;
	case 0:
		phyWrapper.setMovablitiy(Movablitiy(0, 1, 1, 1));
		object.move = phyWrapper.getMovablitiy();
		break;
	case 1:
		phyWrapper.setMovablitiy(Movablitiy(1, 1, 1, 0));
		object.move = phyWrapper.getMovablitiy();
		break;
	default:
		phyWrapper.setMovablitiy(Movablitiy(1, 1, 1, 1));
		object.move = phyWrapper.getMovablitiy();
		break;
	}
}

float GamePhysics::Bisection(float speed)
{
	Vector2 deltas = CalculateDeltas();

	if (CheckCollision(abs(deltas.x) - speed, abs(deltas.y) - speed)) return speed;
	Bisection((speed + 0.01f) / 2);
	b_nextStepCollisionTriggered = true;
	
}

void GamePhysics::CalculateNextStep()
{
	Vector2 deltas = CalculateDeltas();
	PhysicsComponent PhysicsObject1(m_currentObject);
	PhysicsComponent PhysicsObject2(m_targetObject);
	if (!CheckCollision(abs(deltas.x) - 0.01f, abs(deltas.y) - 0.01f)) return;
	float distance = Bisection(0);

	PhysicsObject1.setVelocity(distance);
	PhysicsObject2.setVelocity(distance);
	m_currentObject->velocity = PhysicsObject1.getVelocity();
	m_targetObject->velocity = PhysicsObject2.getVelocity();
}
