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

void GamePhysics::Render(float dt)
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
			b_nextStepCollisionTriggered = false;

			if (PhysicsObject1.getID() == PhysicsObject2.getID())
				continue;
			if (PhysicsObject2.getCollision() != Collision::CAN_COLLIDE)
				continue;
			MovementDefinition* ob1 = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(m_currentObject->parentId);
			MovementDefinition* ob2 = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(m_targetObject->parentId);

			if (!b_nextStepCollisionTriggered)
				CalculateNextStep(dt);

			if (!CheckCollision(CalculateDeltas().x, CalculateDeltas().y)) {
				UpdateMovability(*m_currentObject, Direction::RESET);
				continue;
			}

			DoCollisionSteps();


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

	if (intersectX < 0.0f && intersectY < 0.0f)
		return 1;

	return 0;
}

void GameEngine::GamePhysics::DoCollisionSteps()
{
	GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
	PhysicsComponent PhysicsObject1(m_currentObject);
	PhysicsComponent PhysicsObject2(m_targetObject);

	UpdateMovability(*m_currentObject, CollisionDirection(m_currentObject, m_targetObject));
	UpdateMovability(*m_targetObject, CollisionDirection(m_targetObject, m_currentObject));


	PhysicsSubject& PhysicsSubject = PhysicsSubject::GetInstance();
	PhysicsSubject.Notify(ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject1.getParentID())), ObjectHandler.GetGameObject(ObjectHandler.GetGameObjectIndex(PhysicsObject2.getParentID())));
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
	switch (direction)
	{
	case Direction::DOWN:
		phyWrapper.setMovablitiy(Movablitiy(phyWrapper.getMovablitiy().up, 0, phyWrapper.getMovablitiy().left, phyWrapper.getMovablitiy().right));
		break;
	case Direction::LEFT:
		phyWrapper.setMovablitiy(Movablitiy(phyWrapper.getMovablitiy().up, phyWrapper.getMovablitiy().down, 0, phyWrapper.getMovablitiy().right));
		break;
	case Direction::UP:
		phyWrapper.setMovablitiy(Movablitiy(0, phyWrapper.getMovablitiy().down, phyWrapper.getMovablitiy().left, phyWrapper.getMovablitiy().right));
		break;
	case Direction::RIGHT:
		phyWrapper.setMovablitiy(Movablitiy(phyWrapper.getMovablitiy().up, phyWrapper.getMovablitiy().down, phyWrapper.getMovablitiy().left, 0));
		break;
	default:
		phyWrapper.setMovablitiy(Movablitiy(1, 1, 1, 1));
		break;
	}
	object.move = phyWrapper.getMovablitiy();
}

float GamePhysics::Bisection(float speed)
{
	if (CheckCollision(abs(CalculateDeltas().x) - speed, abs(CalculateDeltas().y) - speed)) return speed;
	Bisection((speed + 1.f) / 2);
	b_nextStepCollisionTriggered = true;
}

void GamePhysics::CalculateNextStep(float dt)
{
	MovementDefinition* ob1 = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(m_currentObject->parentId);
	MovementDefinition* ob2 = GameInputHandler::GetInstance().GetMovementDefinitionByParentID(m_targetObject->parentId);
	if (CheckCollision(abs(CalculateDeltas().x) - (ob1->speed * dt *2), abs(CalculateDeltas().y) - (ob1->speed * dt *2)) == 0) return;

	
	//std::cout << (int)CollisionDirection(m_currentObject, m_targetObject) << " physics." << std::endl;
	float distance = Bisection(0);
	//std::cout << distance << " distance" << std::endl;
	if (distance <= 0)
	{
		ob1->speed = ob1->maxSpeed;
		ob2->speed = ob2->maxSpeed;
		return;
	}
	ob1->speed = ob1->speed * distance;
	ob2->speed = ob1->speed * distance;
}