#pragma once
namespace GameEngine {
	struct Movablitiy {
		Movablitiy() {
			up = 1;
			down = 1;
			left = 1;
			right = 1;
		}
		Movablitiy(int f, int b, int l, int r) {
			up = f;
			down = b;
			left = l;
			right = r;
		}
		int up;
		int down;
		int left;
		int right;
	};
	struct PlayerDefinition {};
	struct Definition {};
}
