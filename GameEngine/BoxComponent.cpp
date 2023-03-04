#include "BoxComponent.h"
using namespace GameEngine;

BoxComponent::BoxComponent()
{
	m_sizeMultiplier = 1;
}

BoxComponent::BoxComponent(float size)
{
	m_sizeMultiplier = size;
	SetVertices({ -1.f * (size/2), -1.f * (size/2), 1.f * (size/2), -1.f * (size/2), 1.f * (size/2), 1.f * (size/2), -1.f * (size/2), 1.f * (size/2) });
}
BoxComponent::BoxComponent(float width, float height)
{
	SetVertices({ -1.f * (width/2), -1.f * (height/2), 1.f * (width/2), -1.f * (height/2), 1.f * (width/2), 1.f * (height/2), -1.f * (width/2), 1.f * (height/2) });
}