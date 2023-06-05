#include "HoG.h"
#include <math.h>
#include "Filter.h"


void drawHistOnCell(Image<short>& image, int x, int y, int cellSize, short* hist, int nBins)
{
	int halfCellSize = cellSize / 2;
	int centerX = x + halfCellSize;
	int centerY = y - halfCellSize;
	double angle = 180 / nBins;

	for (int k = 0; k < nBins; k++)
	{
		double currentAngle = angle * k;

		for (int i = 0; i < halfCellSize; i++)
			for (int j = 0; j < halfCellSize; j++)
			{
				image(centerX + i * cos(currentAngle) - 1, centerY - j * sin(currentAngle)) += hist[k];
				image(centerX - i * cos(currentAngle), centerY + j * sin(currentAngle) - 1) += hist[k];
			}				
	}
}

Image<short> HoG::createImage()
{
	int imageRowEnd = hogImage.rows / cellSize * cellSize;
	int imageColEnd = hogImage.cols / cellSize * cellSize;

	Image<short> outImage(imageRowEnd, imageColEnd);

	for (int x = 0; x < imageColEnd; x += cellSize)
	{
		for (int y = 0; y < imageRowEnd; y += cellSize)
		{
			drawHistOnCell(outImage, x, y, cellSize, hists[x * imageColEnd + y], this->nBins);
		}
	}
	return outImage;
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
short* createHistInCell(int x, int y, Image<short> Ix, Image<short> Iy, int cellSize, int nBins)
{
	short* hist = new short[nBins];
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
			hist[(position + 1) % nBins] += coeff * magnitude;
		}
	}

	return hist;
}

/// <summary>
/// √истограммы ориентированных градиентов
/// </summary>
/// <param name="image">картинка</param>
/// <param name="cellSize">размер блока дл€ 1 гистограммы</param>
/// <param name="nBins">кол-во €чеек в гистограмме</param>
HoG::HoG(Image<short> image, int cellSize, int nBins)
{
	this->nBins = nBins;
	this->cellSize = cellSize;
	this->hogImage = image.clone();
	Image<short> Ix = Filter::sobel(image, 3, 0); // TODO
	Image<short> Iy = Filter::sobel(image, 3, 1); // TODO
	

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

vector<short*> HoG::getHistograms()
{
	return hists;
}


