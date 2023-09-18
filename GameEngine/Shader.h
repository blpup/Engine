#pragma once
#include <string>
#include "Vector2.h"
#include "Color3.h"

namespace GameEngine {
	class Shader
	{
	public:
		unsigned int CreateShader(const std::string& vertextShader, const std::string& fragmentShader);
		std::string CreateVertexShader();
		std::string CreateFragmentShader();
	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
	};
}


