#include "GameRenderer.h"
#include "GameObjectHandler.h"
#include "RenderComponent.h"
#include "GameObject.h";
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
using namespace GameEngine;
GameRenderer& GameRenderer::GetInstance()
{
    static GameRenderer instance;
    return instance;
}

void GameRenderer::Add(RenderObject* object)
{
    Objects.push_back(object);
    if (Objects.size() > 1) {
        Sort();
    }
}

void GameRenderer::Remove(RenderObject* object)
{
    RenderComponent RenderObject(object);
    //int location = RenderObject.getID();
    //Objects.erase(Objects.begin() + (location-1));
}

void GameRenderer::Render()
{
    GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
    for (size_t i = 0; i < Objects.size(); i++)
    {
        RenderComponent renWrapper(Objects[i]);
        const size_t objectIndex = ObjectHandler.GetGameObjectIndex(renWrapper.getParentID());
        if (objectIndex < 0) {
            continue;
        }
        GameObject GameObject1(&ObjectHandler.GetGameObject(objectIndex));
        Vector2 position = GameObject1.GetCoords();
        glColor3f(renWrapper.getColor().r, renWrapper.getColor().g, renWrapper.getColor().b);
        glBegin(renWrapper.getRenderType());
        
        for (size_t i = 0; i < renWrapper.getVertices().size(); i += 2)
        {
            glVertex2f(position.x + renWrapper.getVertices()[i], position.y + renWrapper.getVertices()[i + 1]);
        }
        glEnd();

    }
}

int GameRenderer::GetSize()
{
    return Objects.size();
}

void GameRenderer::Sort()
{
    std::sort(Objects.begin(), Objects.end(), [](const RenderObject* lhs, const RenderObject* rhs) {
        RenderComponent o1(lhs);
        RenderComponent o2(rhs);
        return o1.getZIndex() < o2.getZIndex();
     });
}

