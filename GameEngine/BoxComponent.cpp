#include "BoxComponent.h"
using namespace GameEngine;

BoxComponent::BoxComponent()
{
	m_sizeMultiplier = .1;

	SetVertices(
		{
			-1.f * (m_sizeMultiplier / 2), -1.f * (m_sizeMultiplier / 2),
			1.f * (m_sizeMultiplier / 2), -1.f * (m_sizeMultiplier / 2),
			1.f * (m_sizeMultiplier / 2), 1.f * (m_sizeMultiplier / 2),
			-1.f * (m_sizeMultiplier / 2), 1.f * (m_sizeMultiplier / 2)
		}
	);


	SetIndices({ 0,1,2,2,3,0 });
}

BoxComponent::BoxComponent(float size)
{
	m_sizeMultiplier = size;
	SetVertices(
		{
			-1.f * (size / 2),-1.f * (size / 2),
			1.f * (size / 2), -1.f * (size / 2),
			1.f * (size / 2), 1.f * (size / 2),
			-1.f * (size / 2), 1.f * (size / 2)
		}
	);

	SetIndices({ 0,1,2,2,3,0 });
}
BoxComponent::BoxComponent(float width, float height)
{
	SetVertices(
		{
			-1.f * (width / 2), -1.f * (height / 2),
			1.f * (width / 2), -1.f * (height / 2),
			1.f * (width / 2), 1.f * (height / 2),
			-1.f * (width / 2), 1.f * (height / 2)
		}
	);


	SetIndices({ 0,1,2,2,3,0 });
}