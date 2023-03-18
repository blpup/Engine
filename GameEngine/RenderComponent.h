#pragma once
#include "Color3.h"
#include "BoxComponent.h"
#include "UUID.h"
#include <vector>
#include <GLFW/glfw3.h>
namespace GameEngine {
	class UUID;
	class GameObject;
	struct Vector2;

	struct RenderObject {
		RenderObject() {
			color.SetColor(1, 1, 1);
			zIndex = 0;
			renderType = GL_TRIANGLE_FAN;
		}
		UUID id;
		uint64_t parentId;
		Color3 color; // The Color of the object
		int zIndex; // The priority of the object to render in; Painters Algo
		std::vector<float> vertices = BoxComponent().GetVertices(); //The vertices array 
		GLenum renderType;
	};

	class RenderComponent
	{
	public:

		RenderComponent(const RenderObject* object);
		RenderComponent(const RenderObject* object, uint64_t id);
		uint64_t getID();
		uint64_t getParentID();
		void setParentID(uint64_t value);
		Color3 getColor();
		void setColor(Color3 value);
		int getZIndex();
		void setZIndex(int value);
		std::vector<float> getVertices();
		void setVertices(std::vector<float> value);
		GLenum getRenderType();
		void setRenderType(GLenum value);
		void instantiate(RenderObject* object);
	private:
		uint64_t m_id;
		uint64_t m_parentId;
		Color3 m_color;
		int m_zIndex;
		std::vector<float> m_vertices;
		GLenum m_renderType;
	};
}


