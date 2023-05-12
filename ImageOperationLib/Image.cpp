#include "Image.h"
using namespace std;


template<typename T>
Image<T>::Image(string filename)
{

}

template<typename T>
Image<T> Image<T>::createEmptyImg(int rowSize, int colSize)
{
	Image<T> emptyImg;
	emptyImg.image = new T(rowSize * colSize);
	emptyImg.rows = rowSize;
	emptyImg.cols = colSize;

	return emptyImg;
}

template<typename T>
Image<T> Image<T>::convertToGray()
{
	Image<short> grayImg(rows, cols);
	vectorRGB pixel;
	for (int y = 0; y < cols; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			pixel = this->operator(x, y);
			grayImg(x, y) = 0,299 * pixel.red
				+ 0,5876 * pixel.green
				+ 0,114 * pixel.blue;
		}
	}
	return grayImg;
}

template<typename T>
T* Image<T>::operator() (int x, int y)
{
	return *(image + y * cols + x);
}

template<typename T>
Image<T> Image<T>::clone()
{
	Image<T> cloneImg;
	cloneImg.image = new T(rows * cols);
	for (int y = 0; y < cols; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			cloneImg(x, y) = this->operator(x, y);			
		}
	}
	cloneImg.rows = rowSize;
	cloneImg.cols = colSize;

	return cloneImg;
}
