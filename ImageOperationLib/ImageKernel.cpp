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

//-------------------------
// Статические методы
//-------------------------

/// <summary>
/// Получение ядра Гаусса
/// </summary>
/// <param name="size"> размер ядра</param>
/// <param name="sigma"> среднеквадратичное отклонение нормального распределения</param>
/// <returns> ядро Гаусса</returns>
ImageKernel ImageKernel::gauss(int size, int sigma)
{
	ImageKernel gaussImg(size);
	double constWithSigma = 2 * sigma * sigma;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			gaussImg(x, y) = (1 / (constWithSigma * PI))
				* exp(-(x * x + y * y) / constWithSigma);
		}
	}
	return gaussImg;
}

ImageKernel ImageKernel::laplassianGaussian(int size, int sigma)
{

}
