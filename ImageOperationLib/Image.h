#pragma once
#include <iostream>
#include "IClone.h"

using namespace std;

struct vectorRGB {
	short red, green, blue;
};

template <typename T>
class Image : public IClone
{
private:
	T* image;

	Image();
	Image createEmptyImg(int rowSize, int colSize);

public:

	int rows, cols; // ������ � ������� �����������
	/// <summary>
	/// ���������� �������� �� �����
	/// </summary>
	/// <param name="filename"> �������� ����� � �����������</param>
	Image(string filename);

	Image convertToGray();

	T* operator() (int x, int y);

	Image clone();


};


