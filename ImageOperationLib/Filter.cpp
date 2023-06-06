#include "Filter.h"
#include "ExpandImage.h"
#include "ImageKernel.h"

/// <summary>
/// ����� ����
/// </summary>
/// <param name="image">������� ��������</param>
/// <returns>����������� � �������� ������</returns>
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

/// <summary>
/// �����-����� �����������
/// </summary>
/// <param name="image">������� ��������</param>
/// <returns>�����-����� ��������</returns>
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

 /// <summary>
 /// �����-����� �����������
 /// </summary>
 /// <param name="grayImage">�������� � �������� ������</param>
 /// <returns>�����-����� ��������</returns>
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

 /// <summary>
 /// ������ �������
 /// </summary>
 /// <param name="image">������� ��������</param>
 /// <returns></returns>
 Image<vectorRGB> Filter::negative(Image<vectorRGB> image)
 {
	 Image<vectorRGB> negativeImage(image.rows, image.cols);
	 for (int x = 0; x < image.cols; x++)
		 for (int y = 0; y < image.rows; y++)
		 {
			 negativeImage(x, y).red = 255 - image(x, y).red;
			 negativeImage(x, y).green = 255 - image(x, y).green;
			 negativeImage(x, y).blue = 255 - image(x, y).blue;
		 }
	 return negativeImage;
 }


 //==========================================
 // ���� (�� ���� ����� ��� 1 ���� ��� �����)
 //==========================================

 /// <summary>
 /// ��������� ��������� ����������� �� �����
 /// </summary>
 /// <param name="image">��������</param>
 /// <param name="kernel">�����</param>
 /// <returns>������� - ��������� ������������ � ������������</returns>
 vectorRGB multiplyOnMask(int x, int y, Image<vectorRGB> image, ImageKernel kernel)
 {
	 int kernelCenter = kernel.size / 2;
	 vectorRGB point;
	 for (int _x = 0; _x < kernel.size; _x++)	 
		 for (int _y = 0; _y < kernel.size; _y++)
		 {
			 point.red += (kernel(_x, _y) * image(x - kernelCenter + _x, y - kernelCenter + _y).red);
			 point.green += (kernel(_x, _y) * image(x - kernelCenter + _x, y - kernelCenter + _y).green);
			 point.blue += (kernel(_x, _y) * image(x - kernelCenter + _x, y - kernelCenter + _y).blue);
		 }
	 
	 // ������������
	 double normolizeCoeff = kernel.sum();
	 point.red /= normolizeCoeff;
	 point.green /= normolizeCoeff;
	 point.blue /= normolizeCoeff;

	 return point;
 }

 short multiplyOnMask(int x, int y, Image<short> image, ImageKernel kernel)
 {
	 int kernelCenter = kernel.size / 2;
	 short point = 0;
	 for (int _x = 0; _x < kernel.size; _x++)
		 for (int _y = 0; _y < kernel.size; _y++)
		 {
			 point += (kernel(_x, _y) * image(x - kernelCenter + _x, y - kernelCenter + _y));
		 }

	 // ������������
	 double normolizeCoeff = kernel.sum();
	 point /= normolizeCoeff;

	 return point;
 }


 /// <summary>
 /// ���� �������� � ������� �����
 /// </summary>
 /// <param name="image">��������</param>
 /// <param name="kernel">�����</param>
 /// <returns>����������� ��������</returns>
 template<typename T>
 Image<T> blurWithMask(Image<T> image, ImageKernel kernel)
 {
	 int halfMaskSize = kernel.size / 2;
	 int expImgColEnd = halfMaskSize + image.cols;
	 int expImgRowEnd = halfMaskSize + image.rows;
	 Image<T> expImg = ExpandImage::mirror(image, halfMaskSize);
	 Image<T> blurImg(image.rows, image.cols);

	 for (int x = halfMaskSize; x < expImgColEnd; x++)
		 for (int y = halfMaskSize; y < expImgRowEnd; y++)
			 blurImg(x,y) = multiplyOnMask(x, y, image, kernel);

	 return blurImg;
 }



 /// <summary>
 /// ������ ������
 /// </summary>
 /// <param name="image">�������� (�� ����� ��������)</param>
 /// <param name="maskSize">������ ����� (�������� �����)</param>
 /// <param name="sigma">������������������ ���������� ����������� �������������</param>
 /// <returns>����������� �������� ������ ��������</returns>
 Image<vectorRGB> Filter::gaussBlur(Image<vectorRGB> image, int maskSize, double sigma)
 {
	 return blurWithMask(image, ImageKernel::gauss(maskSize, sigma));
 }

 /// <summary>
  /// ������ ���������� ���������
  /// </summary>
  /// <param name="image">�������� (�� ����� ��������)</param>
  /// <param name="maskSize">������ ����� (�������� �����)</param>
  /// <param name="sigma">������������������ ���������� ����������� �������������</param>
  /// <returns>����������� �������� ���������� ��������� ��������</returns>
 Image<vectorRGB> Filter::laplassianGaussianBlur(Image<vectorRGB> image, int maskSize, double sigma)
 {
	 return blurWithMask(image, ImageKernel::laplassianGaussian(maskSize, sigma));
 }


 /// <summary>
 /// ������ ������
 /// </summary>
 /// <param name="image"></param>
 /// <param name="maskSize"></param>
 /// <param name="asix"></param>
 /// <returns></returns>
 Image<short> Filter::sobel(Image<short> image, int maskSize, int asix)
 {
	 return blurWithMask(image, ImageKernel::sobel(maskSize, asix));
 }




 

