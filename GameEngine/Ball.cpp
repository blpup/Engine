#include "Ball.h"
#include "GamePhysics.h"
#include "RenderComponent.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include "AutoMovement.h"

GameEngine::Ball::Ball()
{
	SetSpeed(0.005);
	SetCoords(0, 0);
	circleComponent = new CircleComponent(.02f, GetCoords());
	renderComponent = new RenderComponent(GetCoords(), Color3(1, 0, 0), circleComponent->GetVertices(), 2, GL_TRIANGLE_FAN, *this);
	physicsComponent = new PhysicsComponent(Collision::CAN_COLLIDE, CollisionType::BOUNCE, circleComponent->GetMaxWidth(), circleComponent->GetMaxHeight(), *this);
	
}

void GameEngine::Ball::Update()
{
	new AutoMovement(physicsComponent);
}
