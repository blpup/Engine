#pragma once
struct Movablitiy {
	Movablitiy() {
		forward = 1;
		backward = 1;
		left = 1;
		right = 1;
	}
	Movablitiy(int f, int b, int l, int r) {
		forward = f;
		backward = b;
		left = l;
		right = r;
	}
	int forward;
	int backward;
	int left;
	int right;
};