#include "CircleComponent.h"
using namespace GameEngine;

CircleComponent::CircleComponent(float radius, Vector2 vector):
	m_radius(radius)
{
	std::vector<float> temp;
	for (size_t i = 0; i < 360; i++)
	{
		temp.push_back(vector.x/360 + (radius * cos(i * 2 * 3.14 / 360)));
		temp.push_back(vector.y/360 + (radius * sin(i * 2 * 3.14 / 360)));
	}
	SetVertices(temp);
}
