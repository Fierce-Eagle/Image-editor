#pragma once
#include "Image.h"
#include <vector>

class HoG
{
private:
	Image<short> hogImage;
	int nBins, cellSize;

	vector<short*> hists;
public:

	Image<short> createImage();

	HoG(Image<short> image, int cellSize, int nBins);

	vector<short*> getHistograms();

};

