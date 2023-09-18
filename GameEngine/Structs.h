#pragma once
#include "Entity.h"
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
	struct Ground{};
	struct RotationDefinition {
		RotationDefinition() {
			angle = 0;
			parentId = 0;
		}
		float angle;
		Entity::EntityId parentId;
	};
}
