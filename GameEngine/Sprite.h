#pragma once
#include <cstdint>
namespace GameEngine {
	struct Sprite {
		uint32_t x = 0, y = 0;
	};

	namespace Sprites {
		Sprite GrassEdge{ 0, 0 };
	}
}