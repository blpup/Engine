#include "Wall.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "BoxComponent.h"
#include "PhysicsComponent.h"
#include "MovementComponent.h"
#include "GameInputHandler.h"
#include "Vector2.h"
#include <vector>

using namespace GameEngine;
Wall::Wall()
{
	SetSpeed(0.01);
	SetCoords(.05, -.9);
	boxComponent = new BoxComponent(1.f, .1f);
	renderComponent = new RenderComponent(GetCoords(), Color3(0,1,0), boxComponent->GetVertices(), 2, GL_QUADS, *this);
	physicsComponent = new PhysicsComponent(Collision::CAN_COLLIDE, CollisionType::SOLID, boxComponent->GetMaxWidth(), boxComponent->GetMaxHeight(), *this);
	std::vector<MovementComponent::Keybindings> bindings
	{
		MovementComponent::Keybindings(Direction::UP,GLFW_KEY_I),
		MovementComponent::Keybindings(Direction::DOWN,GLFW_KEY_K),
		MovementComponent::Keybindings(Direction::LEFT,GLFW_KEY_J),
		MovementComponent::Keybindings(Direction::RIGHT,GLFW_KEY_L)
	};
	movementComponent = new MovementComponent(*this, bindings);
	GameInputHandler::GetInstance().AddMovementComponent(movementComponent);
}
