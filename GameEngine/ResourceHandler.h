#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include "stb_image.h"

namespace GameEngine {
	enum class FileType {
		SPRITE
	};
	class ResourceHandler
	{
	public:
		void LoadAsset(FileType type, const char* path);
	private:
		void LoadSpriteSheet(const char* path);
	};
}

