#pragma once
#include "Image.h"


class Filter
{
private:
	Filter(); // ����� ����� ���� �� ������� ������� ��������� �������
public:
	static Image<short> blackWhite(Image<vectorRGB> image);
	static Image<short> blackWhite(Image<short> grayImage);

	static Image<short> gray(Image<vectorRGB> image);

	static Image<vectorRGB> negative(Image<vectorRGB> image);

	//
	// ����
	//
	static Image<vectorRGB> gaussBlur(Image<vectorRGB> image, int maskSize, double sigma);

	static Image<vectorRGB> laplassianGaussianBlur(Image<vectorRGB> image, int maskSize, double sigma);

	static Image<short> sobel(Image<short> image, int maskSize, int asix);

};

