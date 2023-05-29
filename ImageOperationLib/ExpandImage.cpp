#include "ExpandImage.h"

/// <summary>
/// ���������� ����������� ������� ��������������
/// </summary>
/// <typeparam name="T"> ��� ������ (vectorRGB ��� short)</typeparam>
/// <param name="image">��������</param>
/// <param name="padding">������</param>
/// <returns>����������� ����������� �� padding �� ���� ������</returns>
template <typename T>
Image<T> ExpandImage::mirror(Image<T> image, int padding)
{
	Image<T> expMirrorImage(grayImage.rows + 2 * padding, grayImage.cols + 2 * padding);

	// ���������� ������ � �����
	for (int x = 0; x < padding; x++)
		for (int y = 0; y < image.rows; y++)
		{
			expMirrorImage(x, y + padding) = image(padding - x, y);
			expMirrorImage(expMirrorImage.cols - x, y + padding) = image(image.cols - padding - 1 + x, y);
		}

	// ���������� ��������
	for (int x = 0; x < image, cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			expMirrorImage(x + padding, y + padding) = image(x, y);
		}

	// ���������� ������ � �����
	for (int x = 0; x < expMirrorImage.cols; x++)
	{
		for (int y = 0; y < padding; y++)
		{
			expMirrorImage(x, padding - y) = expMirrorImage(x, y);
			expMirrorImage(x, expMirrorImage.rows - padding - 1 + y) = expMirrorImage(x, expMirrorImage.rows - padding - 1 - y);
		}
	}

	return expMirrorImage;
}
