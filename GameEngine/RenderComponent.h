#pragma once
#include "Color3.h"
#include "BoxComponent.h"
#include "UUID.h"
#include "Vertex.h"
#include <vector>
#include <GLFW/glfw3.h>
namespace GameEngine {
	class UUID;
	struct TextureObject {
		int width;
		int height;
		int nrChannels;
		unsigned int texture;
		char* fileLocation = 0;
	};

	struct RenderObject {
		UUID id;
		uint64_t parentId = NULL;
		unsigned int zIndex = 0;
		unsigned int renderType = GL_TRIANGLES;
		unsigned int ibo;
		unsigned int shaderProgram;
		unsigned int vao;
		unsigned int buffer;
		Color3 color{1,1,1};
		TextureObject textureObject;
		std::vector<float> vertices = BoxComponent().GetVertices();
		std::vector<float> combinedVerticesData;
		std::vector<unsigned int> indices = BoxComponent().GetIndicies();
		std::vector<Vertex> verts;
	};



	class RenderComponent
	{
	public:
		RenderComponent(const RenderObject* object);
		std::vector<Vertex> GenerateVertices();
		void instantiate(RenderObject* object);
	private:
		uint64_t m_id;
		uint64_t m_parentId;
		Color3 m_color;
		unsigned int m_zIndex;
		std::vector<float> m_vertices;
		std::vector<Vertex> m_verts;
		unsigned int m_renderType;
	};
}


