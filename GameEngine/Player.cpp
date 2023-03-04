#include "Player.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include <vector>

using namespace GameEngine;
Player::Player()
{
	SetSpeed(0.01);
	SetCoords(.2, .2);
	circleComponent = new CircleComponent(.05f, GetCoords());
	renderComponent = new RenderComponent(GetCoords(), Color3(1,0,0), circleComponent->GetVertices(), 2, GL_TRIANGLE_FAN, *this);
	physicsComponent = new PhysicsComponent(Collision::CAN_COLLIDE, CollisionType::SOLID, circleComponent->GetMaxWidth(), circleComponent->GetMaxHeight(), *this);
	std::vector<MovementComponent::Keybindings> bindings
	{ 
		MovementComponent::Keybindings(Direction::UP,GLFW_KEY_W),
		MovementComponent::Keybindings(Direction::DOWN,GLFW_KEY_S),
		MovementComponent::Keybindings(Direction::LEFT,GLFW_KEY_A),
		MovementComponent::Keybindings(Direction::RIGHT,GLFW_KEY_D)
	};
	movementComponent = new MovementComponent(*this, bindings);
	GameInputHandler::GetInstance().AddMovementComponent(movementComponent);
}

