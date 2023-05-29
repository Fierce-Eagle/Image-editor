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

	double sum();


	//--------------------------------
	// Статические методы
	//--------------------------------
	static ImageKernel sobel(int size);

	static ImageKernel gauss(int size, double sigma);

	static ImageKernel laplassianGaussian(int size, double sigma);
};

