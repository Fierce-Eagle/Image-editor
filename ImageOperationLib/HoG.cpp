#include "HoG.h"
#include <math.h>
#include <list>


template<typename T>
Image<T> HoG::createImage()
{







	return this->hogImage;
}

/// <summary>
/// —оздание гистограммы в область
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="Ix"></param>
/// <param name="Iy"></param>
/// <param name="cellSize"></param>
/// <param name="nBins"></param>
/// <returns></returns>
double* createHistInCell(int x, int y, Image<short> Ix, Image<short> Iy, int cellSize, int nBins)
{
	double* hist = new double[nBins];
	for (int i = 0; i < nBins; i++)
		*(hist + i) = 0;

	int histBinAngleSize = 180 / nBins;
	double magnitude;
	int angle;

	for (int i = 0; i < cellSize; i++)
	{
		for (int j = 0; j < cellSize; j++)
		{
			short gx = Ix(x + i, y + j);
			short gy = Iy(x + i, y + j);
			magnitude = sqrt(gx * gx + gy * gy);
			angle = atan(gy / gx) * 180;

			// 56 / 20 = 2
			int position = angle / histBinAngleSize;
			// (56 % 20) / 20 = 16 / 20
			double coeff = (angle % histBinAngleSize) / static_cast<double>(histBinAngleSize);

			hist[position] += (1 - coeff) * magnitude;
			hist[(position + 1) % nBins] = coeff * magnitude;
		}
	}

	return hist;
}

/// <summary>
/// √истограммы ориентированных градиентов
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="image">картинка</param>
/// <param name="cellSize">размер блока дл€ 1 гистограммы</param>
/// <param name="nBins">кол-во €чеек в гистограмме</param>
template<typename T>
void HoG::solve(Image<T> image, int cellSize, int nBins)
{
	Image<short> Ix = Filter::sobel(image, 3, 0);
	Image<short> Iy = Filter::sobel(image, 3, 1);

	list<double*> hists;

	int imageRowEnd = image.rows / cellSize * cellSize;
	int imageColEnd = image.cols / cellSize * cellSize;

	for (int x = 0; x < imageColEnd; x += cellSize)
	{
		for (int y = 0; y < imageRowEnd; y += cellSize)
		{
			hists.push_back(createHistInCell(x, y, Ix, Iy, cellSize, nBins));
		}
	}

	

}


