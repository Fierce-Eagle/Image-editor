#pragma once
#include "Image.h"

class HoG
{
private:
	template<typename T>
	Image<T> hogImage();
public:
	template<typename T>
	Image<T> createImage();

	template<typename T>
	void solve(Image<T> image, int cellSize, int nBins);

};

