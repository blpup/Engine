#pragma once
#include <vector>
#include "Vector2.h"
#include "Vertex.h"
namespace GameEngine {
	class Shape
	{
	public:
		Shape();
		~Shape();
		std::vector<float> GetVertices();
		std::vector<unsigned int> GetIndicies();
		std::vector<Vertex> GetVerts();
		void SetVertices(std::vector<float> vertices);
		void SetIndices(std::vector<unsigned int> indices);
		float* GetHighLowPoints();
		float* GetLeftRightPoints();
		float GetMaxHeight();
		float GetMaxWidth();
	protected:
		std::vector<float> m_vertices;
		float m_sizeMultiplier;
		float highLowPoint[2];
		float leftRightPoint[2];
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_verts;
	private:
		void CalculatePoints();
	};

}

