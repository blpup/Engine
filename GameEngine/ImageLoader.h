#pragma once
namespace GameEngine {
	class ImageLoader
	{
	public:
		void LoadImage(const char* filename, int* x, int* y, int* channels_in_file, int desired_channels);
	};

}

