#pragma once
#include "Image.h"

class ImageKernel
{
private:
	ImageKernel();
	double* matrix;
public:
	int size;

	ImageKernel(int size);

	double& operator() (int x, int y);


	//--------------------------------
	// Статические методы
	//--------------------------------
	static ImageKernel sobel(int size);

	/// <summary>
	/// Получение ядра Гаусса
	/// </summary>
	/// <param name="size"> размер ядра</param>
	/// <param name="sigma"> среднеквадратичное отклонение нормального распределения</param>
	/// <returns> ядро Гаусса</returns>
	static ImageKernel gauss(int size, int sigma);

	static ImageKernel laplassianGaussian(int size, int sigma);
};

