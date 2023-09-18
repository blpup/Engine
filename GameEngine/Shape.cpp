#include "Shape.h"
#include <iostream>
using namespace GameEngine;

Shape::Shape()
{
}

Shape::~Shape()
{
}

std::vector<float> Shape::GetVertices()
{
	return m_vertices;
}

std::vector<unsigned int> GameEngine::Shape::GetIndicies()
{
	return m_indices;
}

std::vector<Vertex> GameEngine::Shape::GetVerts()
{
	return m_verts;
}

void Shape::SetVertices(std::vector<float> vertices)
{
	m_vertices = vertices;
	CalculatePoints();
}

void GameEngine::Shape::SetIndices(std::vector<unsigned int> indices)
{
	m_indices = indices;
}

float* GameEngine::Shape::GetHighLowPoints()
{
	return highLowPoint;
}

float* GameEngine::Shape::GetLeftRightPoints()
{
	return leftRightPoint;
}

float GameEngine::Shape::GetMaxHeight()
{
	return highLowPoint[0] - highLowPoint[1];
}

float GameEngine::Shape::GetMaxWidth()
{
	return leftRightPoint[0] - leftRightPoint[1];
}

void Shape::CalculatePoints()
{
	highLowPoint[0], highLowPoint[1] = m_vertices[1];
	leftRightPoint[0], leftRightPoint[1] = m_vertices[0];
	for (size_t i = 0; i < m_vertices.size(); i+=2)
	{
		if (highLowPoint[0] < m_vertices[i + 1]) {
			highLowPoint[0] = m_vertices[i +1];
		}
		if (highLowPoint[1] > m_vertices[i + 1]) {
			highLowPoint[1] = m_vertices[i + 1];
		}
		if (leftRightPoint[0] < m_vertices[i]) {
			leftRightPoint[0] = m_vertices[i];
		}
		if (leftRightPoint[1] > m_vertices[i]) {
			leftRightPoint[1] = m_vertices[i];
		}
	}
}
