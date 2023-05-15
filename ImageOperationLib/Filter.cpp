#include "Filter.h"

Image<short> Filter::gray(Image<vectorRGB> image)
{
	Image<short> grayImg(image.rows, image.cols);
	vectorRGB pixel;
	for (int y = 0; y < image.cols; y++)
	{
		for (int x = 0; x < image.rows; x++)
		{
			pixel = image(x, y);
			grayImg(x, y) = 0, 299 * pixel.red
				+ 0, 5876 * pixel.green
				+ 0, 114 * pixel.blue;
		}
	}
	return grayImg;
}

Image<short> Filter::blackWhite(Image<vectorRGB> image)
{
	Image<short> bwImage(image.rows, image.cols);
	Image<short> grayImage = Filter::gray(image);

	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			if (grayImage(x, y) < 128)
				bwImage(x, y) = 0;
			else
				bwImage(x, y) = 255;
		}
	return bwImage;
}

 Image<short> Filter::blackWhite(Image<short> grayImage)
 {
	 Image<short> bwImage(grayImage.rows, grayImage.cols);

	 for (int x = 0; x < grayImage.cols; x++)
		 for (int y = 0; y < grayImage.rows; y++)
		 {
			 if (grayImage(x, y) < 128)
				 bwImage(x, y) = 0;
			 else
				 bwImage(x, y) = 255;
		 }
	 return bwImage;
 }



 template <typename T>
 Image<T> Filter::grubCut(Image<T> image)
 {

 }
