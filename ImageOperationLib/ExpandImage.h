#pragma once
#include "Image.h"

class ExpandImage
{
public:
	template <typename T>
	static Image<T> mirror(Image<T> image, int padding);
};

