#pragma once
#include <opencv2/opencv.hpp>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <functional>
#include <map>
#include <vector>

cv::Mat GTranspose(const cv::Mat image);
cv::Mat inverse(const cv::Mat image);
float interpolate_nearest(const cv::Mat image, float y, float x);
float interpolate_bilinear(const cv::Mat image, float y, float x);

std::map<uchar, int> histogram(const cv::Mat& image);
std::map<uchar, int> histogram_cumul(const cv::Mat& image);
void show_histogram(std::map<uchar, int> &hist);
void evalMinMax(const cv::Mat& image, int& vMin, int& vMax);

cv::Mat expand(const cv::Mat& image);
cv::Mat threshold(const cv::Mat& image, uchar value, bool high);
cv::Mat thresholdCombined(const cv::Mat& image, uchar value);
cv::Mat normalize(const cv::Mat& image, int fMin, int fMax);
cv::Mat quantize(const cv::Mat& image, int layers);
cv::Mat equalize(const cv::Mat& image);

float varianceBetweenClass(std::map<uchar, int> &hist, int& threshold);
cv::Mat thresholdOtsu(const cv::Mat& image);

