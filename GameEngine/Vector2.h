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
		void SetVector2(Vector2 other) {
			x = other.x;
			y = other.y;
		}
		Vector2 operator-(const Vector2& obj) {
			Vector2 temp;
			temp.x = x - obj.x;
			temp.y = y - obj.y;
			return temp;
		}

	};
}