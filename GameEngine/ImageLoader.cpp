#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ImageLoader.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

void GameEngine::ImageLoader::LoadImage(const char* filename, int* x, int* y, int* channels_in_file, int desired_channels)
{
    if (!filename) return;
	unsigned char* data = stbi_load(filename, x, y, channels_in_file, desired_channels);
    
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *x, *y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load image texture " << stbi_failure_reason() << std::endl;
    }
}
