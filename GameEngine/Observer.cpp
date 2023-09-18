#include "Observer.h"

void GameEngine::PhysicsSubject::Attach(OnCollideObserver observer)
{
	m_observers.push_back(observer);
}

void GameEngine::PhysicsSubject::Detach(IObserver* observer)
{
}

void GameEngine::PhysicsSubject::Notify(const GameObjectDefinition& otherEntity, const GameObjectDefinition& currentEntity)
{
	for (size_t i = 0; i < m_observers.size(); i++)
	{
		//Check if ids match to update apporiate components only
		if(currentEntity.id == m_observers[i].GetID())
			m_observers[i].Update(otherEntity);
	}
}

GameEngine::PhysicsSubject& GameEngine::PhysicsSubject::GetInstance()
{
	static PhysicsSubject instance;
	return instance;
}

GameEngine::OnCollideObserver::OnCollideObserver(func callback, uint64_t id){
	m_function = callback;
	m_id = id;
}

void GameEngine::OnCollideObserver::Update(const GameObjectDefinition& entity)
{
	m_function(&entity);
}
