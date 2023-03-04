#include "GameObjectHandler.h"
#include "GameObject.h"
using namespace GameEngine;

GameObjectHandler& GameObjectHandler::GetInstance()
{
    static GameObjectHandler instance;
    return instance;
}

void GameObjectHandler::Add(GameObject* component)
{
    m_objects.push_back(component);
}

void GameObjectHandler::Remove(GameObject* component)
{
}

void GameEngine::GameObjectHandler::Render()
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->Update();
    }
}

std::vector<GameObject*> GameObjectHandler::GetObjects()
{
    return m_objects;
}
