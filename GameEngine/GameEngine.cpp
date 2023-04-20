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

//#include "GameMovement.h"

using namespace GameEngine;
int main(void)
{
    GLFWwindow* window;
    GameInputHandler& InputHandle = GameInputHandler::GetInstance();
    GameRenderer& RendererSystem = GameRenderer::GetInstance();
    GamePhysics& PhysicsSystem = GamePhysics::GetInstance();
    GameObjectHandler& ObjectHandler = GameObjectHandler::GetInstance();
    GameTimeStep& TimeStepSystem = GameTimeStep::GetInstance();
    PhysicsSubject& PhysicsSubject = PhysicsSubject::GetInstance();
    //GameMovement& MovementSystem = GameMovement::GetInstance();
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 900, "Game Engine", NULL, NULL);
    
    new Ball();
    Player* player1 = new Player();
    Player* player2 = new Player();
    player2->m_gameObject.position.SetVector2(0.9, 0);
    player2->m_movementObject.keybindings =
    {
        Keybindings(Direction::UP,GLFW_KEY_I),
        Keybindings(Direction::DOWN,GLFW_KEY_K),
     };
    Wall* TopWall = new Wall();
    Wall* BottomWall = new Wall();
    TopWall->m_gameObject.position.SetVector2(0, 1);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        TimeStepSystem.StartTimeStep();
        glClear(GL_COLOR_BUFFER_BIT);

        ObjectHandler.Render();
        RendererSystem.Render();
        PhysicsSystem.Render();
        InputHandle.Render();
        glfwSetKeyCallback(window, &GameInputHandler::ButtonCallback);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        TimeStepSystem.EndTimeStep();
        //std::cout << TimeStepSystem.GetFPS() << std::endl;
    }

    glfwTerminate();
    return 0;
}
