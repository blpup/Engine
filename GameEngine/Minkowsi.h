#pragma once
namespace GameEngine {
	struct GJK {
		float x;
		float y;
		GJK() = default;
		GJK(float xCoord, float yCoord) {
			x = xCoord;
			y = yCoord;
		}
		void SetVector2(float xCoord, float yCoord) {
			x = xCoord;
			y = yCoord;
		}
	};
}