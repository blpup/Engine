#pragma once
#include "Color3.h";
#include "Vector3.h";
#include <vector>
namespace GameEngine {
	struct Vertex {
		float position[3];
		float color[3]{1.0f, 1.0f, 0.f};
	};

	namespace vmath  {
		inline void CombineVerticesValues(std::vector<float>& arr, const std::vector<Vertex>& vertices, const float *textureCoord) {
			int i = 0;
			for(auto& vertex : vertices)
			{
				arr.push_back(vertex.position[0]);
				arr.push_back(vertex.position[1]);
				arr.push_back(vertex.position[2]);
				arr.push_back(vertex.color[0]);
				arr.push_back(vertex.color[1]);
				arr.push_back(vertex.color[2]);
				arr.push_back(textureCoord[i]);
				arr.push_back(textureCoord[i + 1]);
				i += 2;
			}
		}
	}
}
