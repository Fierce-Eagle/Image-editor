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
	// ����������� ������
	//--------------------------------
	static ImageKernel sobel(int size);

	/// <summary>
	/// ��������� ���� ������
	/// </summary>
	/// <param name="size"> ������ ����</param>
	/// <param name="sigma"> ������������������ ���������� ����������� �������������</param>
	/// <returns> ���� ������</returns>
	static ImageKernel gauss(int size, int sigma);

	static ImageKernel laplassianGaussian(int size, int sigma);
};

