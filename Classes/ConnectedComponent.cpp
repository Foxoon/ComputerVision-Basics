#include "../stdafx.h"

#include "ConnectedComponent.h"


cv::Mat componentsBuffer(const cv::Mat& image) {

	cv::Mat ccBuffer = cv::Mat::zeros(image.cols, image.rows, false);
	cv::Mat visitBuffer = cv::Mat::zeros(image.cols, image.rows, false);

	int componentsCounter = 0;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			int pixel = (int) image.at<uchar>(i, j);

			findComponent(image, ccBuffer, visitBuffer, new cPixel(i, j, pixel), componentsCounter);
			
		}
	}

	return ccBuffer;
}

void findComponent(const cv::Mat& image, cv::Mat& ccBuffer, cv::Mat& visitBuffer, cPixel* origin, const int& componentsCounter) {
	std::vector<cPixel*> pixels;
	pixels.push_back(origin);
	
	while (!pixels.empty()) {
		cPixel* pixel = pixels.back();
		pixels.pop_back();
		
		//std::cout << "0 =" << visitBuffer.size[0] << ", 1=" << visitBuffer.size[1] << std::endl;
		if (visitBuffer.at<uchar>(pixel->y, pixel->x) == 0){
			visitBuffer.at<uchar>(pixel->y, pixel->x) = 1;
			
			if (pixel->value == origin->value && ccBuffer.at<uchar>(pixel->y, pixel->x) == 0) {
				ccBuffer.at<uchar>(pixel->y, pixel->x) = componentsCounter;

					std::vector<cPixel*> neighboors = findNeighboors4(image, pixel);
					pixels.insert(std::end(pixels), std::begin(neighboors), std::end(neighboors));

			}
		}
	}

}

// find the direct neighboors
std::vector<cPixel*> findNeighboors4(const cv::Mat& image, cPixel* pixel) {
	std::vector<cPixel*> pixels;

	// ! top to bottom Coordinates in 2d

	cPixel* temp;
	//left
	temp = getPixelFromMat(image, pixel->y, pixel->x - 1);
	if (temp != NULL)
		pixels.push_back(temp);
	
	//right
	temp = getPixelFromMat(image, pixel->y, pixel->x + 1);
	if (temp != NULL)
		pixels.push_back(temp);

	//top
	temp = getPixelFromMat(image, pixel->y - 1, pixel->x);
	if (temp != NULL)
		pixels.push_back(temp);

	//bottom
	temp = getPixelFromMat(image, pixel->y + 1, pixel->x);
	if (temp != NULL)
		pixels.push_back(temp);

	return pixels;
}

std::vector<cPixel*> findNeighboors8(const cv::Mat& image, cPixel* pixel){
	std::vector<cPixel*> pixels;
	pixels = findNeighboors4(image, pixel);

	cPixel* temp;
	//up-left
	temp = getPixelFromMat(image, pixel->y - 1, pixel->x - 1);
	if (temp != NULL)
		pixels.push_back(temp);

	//up-right
	temp = getPixelFromMat(image, pixel->y - 1, pixel->x + 1 );
	if (temp != NULL)
		pixels.push_back(temp);

	//bottom-left
	temp = getPixelFromMat(image, pixel->y + 1, pixel->x - 1);
	if (temp != NULL)
		pixels.push_back(temp);

	//bottom-right
	temp = getPixelFromMat(image, pixel->y + 1, pixel->x + 1);
	if (temp != NULL)
		pixels.push_back(temp);

	return pixels;
}

cPixel* getPixelFromMat(const cv::Mat& image, int y, int x) {
	if (isInImage(image, y, x)) {
		cPixel* pixel = new cPixel(x, y);
		pixel->value = (float)image.at<uchar>(y, x);
		
		return pixel;
	}

	return NULL;
}

bool isInImage(const cv::Mat& image, int y, int x) {
	if (x >= 0 && x< image.cols && y>= 0 && y < image.rows)
		return true;
	return false;
}

std::vector<uchar> rdmColors(int maxComponent) {
	std::vector<uchar> colors;
	colors.push_back(0);

	for (int i = 1; i < maxComponent + 1; i++) {
		uchar color = (uchar) rand() % 255 + 1;
		colors.push_back(color);
	}
	return colors;
}

