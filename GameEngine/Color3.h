#pragma once
namespace GameEngine {
	struct Color3 {
		float r;
		float g;
		float b;
		Color3() = default;
		Color3(float red, float green, float blue) {
			r = red;
			g = green;
			b = blue;
		}
		void SetColor(float red, float green, float blue) {
			r = red;
			g = green;
			b = blue;
		}
	};

}