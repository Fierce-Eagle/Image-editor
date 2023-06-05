#include "Image.h"
using namespace std;

template<typename T>
Image<T>::Image()
{
}

/// <summary>
/// Считывание картинки из файла
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="filename"> название файла с расширением</param>
template<typename T>
Image<T>::Image(string filename)
{
	// TODO
}

template<typename T>
Image<T>::Image(int rowSize, int colSize)
{
	Image<T> emptyImg();
	emptyImg.image = new T(rowSize * colSize);
	emptyImg.rows = rowSize;
	emptyImg.cols = colSize;
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			emptyImg(x, y) = 0;
		}
	}

	return emptyImg;
}

template<typename T>
T& Image<T>::operator() (int x, int y)
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

/// <summary>
/// Сохранение картинки
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="filename"> название файла с расширением</param>
template<typename T>
void Image<T>::save(string filename)
{
	// TODO
}
