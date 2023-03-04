#pragma once
#include "Vector2.h"
#include "Color3.h"
#include <vector>
#include <GLFW/glfw3.h>
namespace GameEngine {
	class RenderComponent
	{
	public:
		struct RenderObject {
			int m_ID;
			Vector2 m_position; //Position of the object
			Color3 m_color; // The Color of the object
			int m_zIndex; // The priority of the object to render in; Painters Algo
			std::vector<float> m_vertices; //The vertices array 
			GLenum m_renderType;
		};
		RenderComponent(Vector2 position, Color3 color, std::vector<float> vertices, int zIndex,  GLenum renderType, class GameObject& object);
		RenderObject GetRenderObject() const;
		GameObject& GetAttachedObject() const;
	private:
		RenderObject m_RenderObject{};
		GameObject& m_object;
	};
}


