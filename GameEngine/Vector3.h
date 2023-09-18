#pragma once
namespace GameEngine {
	struct Vector3 {
		float x;
		float y;
		float z;
		Vector3() = default;
		Vector3(float xCoord, float yCoord, float zCoord) {
			x = xCoord;
			y = yCoord;
			z = zCoord;
		}
		void SetVector3(float xCoord, float yCoord, float zCoord) {
			x = xCoord;
			y = yCoord;
			z = zCoord;
		}
		void SetVector3(Vector3 other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		Vector3 operator-(const Vector3& obj) {
			Vector3 temp;
			temp.x = x - obj.x;
			temp.y = y - obj.y;
			temp.z = z - obj.z;
			return temp;
		}

	};
}