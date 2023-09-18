#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Wall.h"
#include "Player.h"
#include "Ball.h"
#include "GameObject.h"
#include "GameInputHandler.h"
#include "GameRenderer.h"
#include "GameObjectHandler.h"
#include "GameTimeStep.h"
#include "Observer.h"
#include "OrthographicCamera.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/string_cast.hpp>
#include <memory>

//#include "GameMovement.h"

using namespace GameEngine;

int main(void)
{
    GLFWwindow* window;
    GameInputHandler& InputHandle = GameInputHandler::GetInstance();
    GameRenderer& RendererSystem = GameRenderer::GetInstance();
    GamePhysics& PhysicsSystem = GamePhysics::GetInstance();
    GameTimeStep& TimeStepSystem = GameTimeStep::GetInstance();
    std::unique_ptr<OrthographicCamera> camera(new OrthographicCamera(-1.f, 1.f, 1.f, -1.f));
    camera->SetPosition(glm::vec3(0,0,0));
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1500, 600, "Game Engine", NULL, NULL);
    
    //Game Objects
    std::unique_ptr<Player> player1(new Player);
    std::unique_ptr<Wall> bottomWall(new Wall);
    //Game Objects end

    //Levels

    std::unique_ptr<Wall> platform1(new Wall(.2f, .2f));
    platform1->m_gameObject.position.SetVector2(-.3, -.6);
    std::unique_ptr<Wall> platform3(new Wall(.1f, .1f));
    platform3->m_gameObject.position.SetVector2(-.1, -.4);
    std::unique_ptr<Wall> platform4(new Wall(.1f, .1f));
    platform4->m_gameObject.position.SetVector2(.1, -.2);
    std::unique_ptr<Wall> platform5(new Wall(.1f, .1f));
    platform5->m_gameObject.position.SetVector2(.3, 0);
    std::unique_ptr<Wall> longWall(new Wall(.1f, 1.f));
    longWall->m_gameObject.position.SetVector2(.7f, -.5f);

    //std::unique_ptr<Wall> finishPole(new Wall(.03f, .8f));
    //finishPole->m_gameObject.position.SetVector2(1.3f, -0.6f);
    //finishPole->m_renderObject.color = Color3(0, 1, 0);

    float timeStepAccumulator = 0.f;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    RendererSystem.GenerateBuffers();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        camera->LockToObject(&player1->m_gameObject);
        TimeStepSystem.StartTimeStep();
        float deltaTime = fmin(TimeStepSystem.GetSecondsPerFrame(), TimeStepSystem.idealFramerate);
        timeStepAccumulator += deltaTime;
        glClear(GL_COLOR_BUFFER_BIT);
        while (timeStepAccumulator >= TimeStepSystem.idealFramerate) {
            
            PhysicsSystem.Render(deltaTime);
            InputHandle.Render(deltaTime);
            timeStepAccumulator -= deltaTime;
        }
        
        glfwSetKeyCallback(window, &GameInputHandler::ButtonCallback);
        
        RendererSystem.Render(camera);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        TimeStepSystem.EndTimeStep();
        
    }

    glfwTerminate();
    return 0;
}