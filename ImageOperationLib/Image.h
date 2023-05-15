#pragma once
#include <iostream>
#include "IClone.h"

using namespace std;

struct vectorRGB {
	short red, green, blue;
};

template <typename T>
class Image : public IClone<Image<T>>
{
private:
	T* image;

	Image();
	
public:

	int rows, cols; // строки и столбцы изображени€
	/// <summary>
	/// —читывание картинки из файла
	/// </summary>
	/// <param name="filename"> название файла с расширением</param>
	Image(string filename);

	Image(int rowSize, int colSize);

	T& operator() (int x, int y);

	Image<T> clone();


};


