#include "ResourceHandler.h"
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GameEngine::ResourceHandler::LoadAsset(FileType type, const char* path)
{
	if (type == FileType::SPRITE) {
		LoadSpriteSheet(path);
	}
}

void GameEngine::ResourceHandler::LoadSpriteSheet(const char* path)
{
	int width, height, nrChannels;
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	//glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

