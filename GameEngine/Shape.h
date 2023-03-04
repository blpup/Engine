#pragma once
#include <vector>
#include "Vector2.h"
namespace GameEngine {
	class Shape
	{
	public:
		Shape();
		~Shape();
		std::vector<float> GetVertices();
		void SetVertices(std::vector<float> vertices);
		float* GetHighLowPoints();
		float* GetLeftRightPoints();
		float GetMaxHeight();
		float GetMaxWidth();
	protected:
		std::vector<float> m_vertices;
		float m_sizeMultiplier;
		float highLowPoint[2];
		float leftRightPoint[2];
	private:
		void CalculatePoints();
	};

}

