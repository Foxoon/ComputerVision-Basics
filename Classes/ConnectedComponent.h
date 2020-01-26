#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <stack>
#include "cPixel.h"
#include <string>

cv::Mat componentsBuffer(const cv::Mat& image);
void findComponent(const cv::Mat& image, cv::Mat& ccBuffer, cv::Mat& visitBuffer, cPixel* origin, const int& componentsCounter);
std::vector<cPixel*> findNeighboors4(const cv::Mat& image, cPixel* pixel);
std::vector<cPixel*> findNeighboors8(const cv::Mat& image, cPixel* pixel);

cPixel* getPixelFromMat(const cv::Mat& image, int y, int x);
bool isInImage(const cv::Mat& image, int y, int x);
std::vector<uchar> rdmColors(int maxComponent);

