#ifndef OUTILITYFUNCTIONS_H
#define OUTILITYFUNCTIONS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "oPixel.h"
#include <vector>
#endif // OUTILITYFUNCTIONS_H


float interpolate_nearest(cv::Mat image, float y, float x);
float interpolate_bilinear(const cv::Mat image, float y, float x);
oPixel* getPixelFromMat(const cv::Mat& image, int y, int x);
bool isInImage(const cv::Mat& image, int y, int x);
std::vector<uchar> rdmColors(int maxComponent);


float interpolate_nearest(cv::Mat image, float y, float x){
    float v = 0;

int cx = round(x);
int cy = round(y);

v = image.at<uchar>(cy, cx);

return v;
}

float interpolate_bilinear(const cv::Mat image, float y, float x) {
    float v = 0;

    //floored value of the coord
    int x1 = floor(x);
    int y1 = floor(y);

    int x2 = std::min(x1 + 1, image.cols - 1);
    int y2 = std::min(y1 + 1, image.rows - 1);

    float alpha = (x - x1) / (x2 - x1);
    float beta = (y - y1) / (y2 - y1);

    float f1 = image.at<uchar>(y1, x1);
    float f12 = image.at<uchar>(y1, x2);

    float f2 = image.at<uchar>(y2, x2);

    float f21 = image.at<uchar>(y2, x1);
    v = (1 - alpha)*(1 - beta)*f1 + alpha * (1 - beta)*f21 + (1 - alpha) * beta * f12 + alpha * beta * f2;

    return v;
}

oPixel* getPixelFromMat(const cv::Mat& image, int y, int x) {
    if (isInImage(image, y, x)) {
        oPixel* pixel = new oPixel(x, y);
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

