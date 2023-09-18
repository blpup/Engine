#include "GameObjectHandler.h"
#include "GameObject.h"
#include "UUID.h"

using namespace GameEngine;

GameObjectHandler& GameObjectHandler::GetInstance()
{
    static GameObjectHandler instance;
    return instance;
}

void GameObjectHandler::Add(GameObjectDefinition& component)
{
    m_objects.push_back(&component);
}

void GameObjectHandler::Remove(GameObject* component)
{
}

void GameEngine::GameObjectHandler::Render()
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        //m_objects[i]->Update();
    }
}

size_t GameEngine::GameObjectHandler::GetGameObjectIndex(uint64_t id)
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        GameObject goWrapper(m_objects[i]);
        if (goWrapper.GetID() == id)
            return i;
        
    }
    return -1;
}

GameObjectDefinition& GameEngine::GameObjectHandler::GetGameObject(size_t index)
{
    return *m_objects[index];
}
