#pragma once
#include "Image.h"


class Filter
{
public:
	static Image<short> blackWhite(Image<vectorRGB> image);
	static Image<short> blackWhite(Image<short> grayImage);

	static Image<short> gray(Image<vectorRGB> image);

	static Image<vectorRGB> negative(Image<vectorRGB> image);


};

