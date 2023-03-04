#include "GameRenderer.h"
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

void GameRenderer::Add(RenderComponent* component)
{
    Objects.push_back(component);
    if (Objects.size() > 1) {
        Sort();
    }
}

void GameRenderer::Remove(RenderComponent* component)
{
    int location = component->GetRenderObject().m_ID;
    Objects.erase(Objects.begin() + (location-1));
}

void GameRenderer::Render()
{
    for (size_t i = 0; i < Objects.size(); i++)
    {
        RenderComponent::RenderObject CurrentObject = Objects[i]->GetRenderObject();
        Vector2 position = Objects[i]->GetAttachedObject().GetCoords();
        glColor3f(CurrentObject.m_color.r, CurrentObject.m_color.g, CurrentObject.m_color.b);
        glBegin(CurrentObject.m_renderType);
        
        for (size_t i = 0; i < CurrentObject.m_vertices.size(); i+=2)
        {
            //std::cout << CurrentObject.m_vertices[i] << CurrentObject.m_vertices[i + 1] << std::endl;
            glVertex2f(position.x + CurrentObject.m_vertices[i], position.y + CurrentObject.m_vertices[i + 1]);
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
    std::sort(Objects.begin(), Objects.end(), [](const RenderComponent* lhs, const RenderComponent* rhs) {
        RenderComponent::RenderObject o1 = lhs->GetRenderObject();
        RenderComponent::RenderObject o2 = rhs->GetRenderObject();
        return o1.m_zIndex < o2.m_zIndex;
        });
}

