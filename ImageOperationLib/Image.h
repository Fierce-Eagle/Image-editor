#pragma once
#include <iostream>
#include "IClone.h"

using namespace std;

struct vectorRGB {
	short red = 0, green = 0, blue = 0;
};

template <typename T>
class Image : public IClone<Image<T>>
{
private:
	T* image;

	
public:

	int rows, cols; // строки и столбцы изображения
	
	Image(string filename);

	Image(int rowSize, int colSize);

	T& operator() (int x, int y);

	Image<T> clone();

	void save(string filename);
};


