#include "ImageKernel.h"
#include <math.h>

# define PI 3.14159265358979323846 

ImageKernel::ImageKernel(int size)
{
	this->size = size;
	int size_2 = size * size;
	matrix = new double[size_2];
	
	for (int i = 0; i < size_2; i++)
		*(matrix + i) = 0;
}

double& ImageKernel::operator() (int x, int y)
{
	return *(matrix + y * size + x);
}

double ImageKernel::sum()
{
	double sum = 0;
	for (int x = 0; x < this->size; x++)
		for (int y = 0; y < this->size; y++)
		{
			sum += this->operator()(x, y);
		}
	return sum;
}

//-------------------------
// Статические методы
//-------------------------

/// <summary>
/// Получение ядра Гаусса
/// </summary>
/// <param name="size"> размер ядра</param>
/// <param name="sigma"> среднеквадратичное отклонение нормального распределения</param>
/// <returns> ядро Гаусса</returns>
ImageKernel ImageKernel::gauss(int size, double sigma)
{
	ImageKernel gaussImg(size);
	const double two_sigma_sigma = 2 * sigma * sigma;
	int halhSize = size / 2;
	int kx, ky;

	for (int x = 0; x < size; x++)
	{
		kx = x - halhSize;
		for (int y = 0; y < size; y++)
		{
			ky = y - halhSize;
			gaussImg(x, y) = (1 / (two_sigma_sigma * PI))
				* exp(-(kx * kx + ky * ky) / two_sigma_sigma);
		}
	}
	return gaussImg;
}

/// <summary>
/// Ядро Лаплассиан-Гауссиана
/// </summary>
/// <param name="size">размер ядра (нечетное число)</param>
/// <param name="sigma">среднеквадратичное отклонение нормального распределения</param>
/// <returns></returns>
ImageKernel ImageKernel::laplassianGaussian(int size, double sigma)
{
	ImageKernel laplassianImg(size);
	const double two_sigma_sigma = 2 * sigma * sigma;
	const double sigma_pow_four = sigma * sigma * sigma * sigma;
	int kx, ky, r;
	int halfSize = size / 2;
	for (int x = 0; x < size; x++)
	{
		kx = x - halfSize;
		for (int y = 0; y < size; y++)
		{
			ky = y - halfSize;
			r = kx * kx + ky * ky;
			laplassianImg(x, y) = ((r - two_sigma_sigma) / sigma_pow_four)
				* exp(-r / two_sigma_sigma);
		}
	}
	return laplassianImg;
}

ImageKernel ImageKernel::sobel(int size, int asix)
{
	ImageKernel sobelKernel(size);

	// TODO
	return sobelKernel;
}
