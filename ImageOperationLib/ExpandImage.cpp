#include "ExpandImage.h"

/// <summary>
/// Расширение изображения методом отзеркаливания
/// </summary>
/// <typeparam name="T"> тип данных (vectorRGB или short)</typeparam>
/// <param name="image">картинка</param>
/// <param name="padding">выступ</param>
/// <returns>изображение расширенное на padding со всех сторон</returns>
template <typename T>
Image<T> ExpandImage::mirror(Image<T> image, int padding)
{
	Image<T> expMirrorImage(grayImage.rows + 2 * padding, grayImage.cols + 2 * padding);

	// заполнение справа и слева
	for (int x = 0; x < padding; x++)
		for (int y = 0; y < image.rows; y++)
		{
			expMirrorImage(x, y + padding) = image(padding - x, y);
			expMirrorImage(expMirrorImage.cols - x, y + padding) = image(image.cols - padding - 1 + x, y);
		}

	// заполнение середины
	for (int x = 0; x < image, cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			expMirrorImage(x + padding, y + padding) = image(x, y);
		}

	// заполнение сверху и снизу
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
