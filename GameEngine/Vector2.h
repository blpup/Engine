#pragma once
namespace GameEngine {
	struct Vector2 {
		float x;
		float y;
		Vector2() = default;
		Vector2(float xCoord, float yCoord) {
			x = xCoord;
			y = yCoord;
		}
		void SetVector2(float xCoord, float yCoord) {
			x = xCoord;
			y = yCoord;
		}
	};
}