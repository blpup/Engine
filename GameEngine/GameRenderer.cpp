#include <GL/glew.h>
#include "GameRenderer.h"
#include "GameObjectHandler.h"
#include "RenderComponent.h"
#include "GameObject.h";
#include "OrthographicCamera.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include "Shader.h"
#include "ImageLoader.h"


using namespace GameEngine;
GameRenderer& GameRenderer::GetInstance()
{
    static GameRenderer instance;
    return instance;
}

void GameRenderer::Add(RenderObject* object)
{
    Objects.push_back(object);
    if (Objects.size() <= 1)
        return;

    Sort();
}

void GameRenderer::Remove(RenderObject* object)
{
}

void GameRenderer::Render(std::unique_ptr<OrthographicCamera>& camera)
{
    GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
    for (size_t i = 0; i < Objects.size(); i++)
    {
        RenderObject* currentObject = Objects[i];
        const size_t objectIndex = ObjectHandler.GetGameObjectIndex(currentObject->parentId);

        if (objectIndex < 0)
            continue;

        GameObject GameObject1(&ObjectHandler.GetGameObject(objectIndex));
        Vector2 position = GameObject1.GetCoords();
        Vector2 cameraShiftedPosition(position.x + camera->m_viewProjectionMatrix[3].x, position.y + camera->m_viewProjectionMatrix[3].y);
        
        
        //std::vector<float> positionAndColor;
        //CalculateRenderPosition(Objects[i]->verts, cameraShiftedPosition);
        //vmath::VertexToFloat(positionAndColor, Objects[i]->verts);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(positionAndColor), &positionAndColor.front(), GL_STATIC_DRAW);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glUseProgram(currentObject->shaderProgram);
        glBindVertexArray(currentObject->vao);
        glDrawElements(currentObject->renderType, 6, GL_UNSIGNED_INT, nullptr);
    }
}

int GameRenderer::GetSize()
{
    return Objects.size();
}

void GameEngine::GameRenderer::CalculateRenderPosition(std::vector<Vertex>& vertices, Vector2 position)
{
    for (auto& vertex : vertices) {
        vertex.position[0] += position.x;
        vertex.position[1] += position.y;
    }
}

void GameRenderer::Sort()
{
    std::sort(Objects.begin(), Objects.end(), [](const RenderObject* lhs, const RenderObject* rhs) {
        return lhs->zIndex < rhs->zIndex;
     });
}

void GameEngine::GameRenderer::GenerateBuffers()
{
    std::unique_ptr<Shader> shader(new Shader());
    GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
    constexpr float textureCoords[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    for (size_t i = 0; i < Objects.size(); i++)
    {
        const size_t objectIndex = ObjectHandler.GetGameObjectIndex(Objects[i]->parentId);
        GameObject GameObject1(&ObjectHandler.GetGameObject(objectIndex));
        RenderObject* currentObject = Objects[i];
        
        std::vector<float> positionColorTexture;
        CalculateRenderPosition(currentObject->verts, GameObject1.GetCoords());
        vmath::CombineVerticesValues(positionColorTexture, currentObject->verts, textureCoords);
        
        //Generate Vertex Array Object and Buffer
        glGenVertexArrays(1, &currentObject->vao);
        glGenBuffers(1, &currentObject->buffer);
        
        //Bind Vertex Array Object
        glBindVertexArray(currentObject->vao);

        glBindBuffer(GL_ARRAY_BUFFER, currentObject->buffer);
        glBufferData(GL_ARRAY_BUFFER, positionColorTexture.size() * sizeof(float), &positionColorTexture.front(), GL_DYNAMIC_DRAW);

        //Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        
        //Colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        //Index Buffer Object
        glGenBuffers(1, &Objects[i]->ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentObject->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(currentObject->indices), &currentObject->indices.front(), GL_DYNAMIC_DRAW);
        
        //Generate texture
        glGenTextures(1, &currentObject->textureObject.texture);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, currentObject->textureObject.texture);
        ImageLoader().LoadImage(currentObject->textureObject.fileLocation, &currentObject->textureObject.width, &currentObject->textureObject.height, &Objects[i]->textureObject.nrChannels, 0);

        std::string vs = shader->CreateVertexShader();
        std::string fs = shader->CreateFragmentShader();
        currentObject->shaderProgram = shader->CreateShader(vs, fs);
    }
}

