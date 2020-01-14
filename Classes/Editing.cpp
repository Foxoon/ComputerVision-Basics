#include "../stdafx.h"

#include "Editing.h"

using namespace std;

cv::Mat inverse(const cv::Mat image) {
	cv::Mat res = image.clone();
	
	for (int i = 0; i < res.rows; i++) {
		for (int j = 0; j < res.cols; j++) {
			uchar intensity = image.at<uchar>(i, j);
			res.at<uchar>(i, j) = 1.0 - intensity;
		}
	}
	return res;
}

cv::Mat GTranspose(const cv::Mat image) {
	cv::Mat res = image.clone();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			res.at<uchar>(i, j) = image.at<uchar>(j, i);
		}
	}
	return res;
}

float interpolate_nearest(cv::Mat image, float y, float x){
	float v = 0;

int cx = round(x);
int cy = round(y);

v = image.at<uchar>(cy, cx);

return v;
}

/**
	Compute the value of a bilinear interpolation in image Mat at position (x,y)
*/
float interpolate_bilinear(const cv::Mat image, float y, float x) {
	float v = 0;

	//floored value of the coord
	int x1 = floor(x);
	int y1 = floor(y);

	int x2 = min(x1 + 1, image.cols - 1);
	int y2 = min(y1 + 1, image.rows - 1);

	float alpha = (x - x1) / (x2 - x1);
	float beta = (y - y1) / (y2 - y1);

	float f1 = image.at<uchar>(y1, x1);
	float f12 = image.at<uchar>(y1, x2);

	float f2 = image.at<uchar>(y2, x2);

	float f21 = image.at<uchar>(y2, x1);
	v = (1 - alpha)*(1 - beta)*f1 + alpha * (1 - beta)*f21 + (1 - alpha) * beta * f12 + alpha * beta * f2;

	return v;

}


std::map<uchar, int> histogram(const cv::Mat& image) {
	std::map<uchar, int> m;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar value = image.at<uchar>(i, j);
			if (m.find(value) != m.end()) {
				++m[value];
			}
			else {
				m[value] = 1;
			}
		}
	}
	return m;

}

std::map<uchar, int> histogram_cumul(const cv::Mat& image) {
	map<uchar, int> m = histogram(image);

	int cumul = 0;

	map<uchar, int>::iterator it;
	double count = 0;
	for (it = m.begin(); it != m.end(); ++it) {
		cumul += it->second;
		it->second = cumul;
	}


	return m;

}

void show_histogram(map<uchar, int> &hist) {
	map<uchar, int>::iterator it;
	std::string str = "Histogram : ----------------------- \n ________________________________\n";
	double count = 0;
	for (it = hist.begin(); it != hist.end(); ++it) {
		str += "|" + to_string(it->first);
		str += "|" + to_string(it->second);
		str += "|\n";
		count +=  it->second;
	}
	str += " Pixels in the image = " + to_string(count);
	str +="\n";
	std:: cout << str << std::endl;
}

/**
	Return the min and max value in grey of the image

*/
void evalMinMax(const cv::Mat& image, uchar& vMin, uchar& vMax) {
	vMin = 255;
	vMax = 0;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = image.at<uchar>(i, j);
			if (oldValue < vMin) {
				vMin = oldValue;
			}
			if (oldValue > vMax) {
				vMax = oldValue;
			}
		}
	}
}


/**
	Double the image resolution using the given interpolation method.
	If the input size is (h,w) the output size shall be (h*2-1, w*2-1)
*/
cv::Mat expand(const cv::Mat &image) {
	cv::Mat res = cv::Mat::zeros(cv::Size(image.rows * 2 - 1, image.cols * 2 - 1), image.type());
	for (int i = 0; i < res.rows; ++i) {
		for (int j = 0; j < res.cols; j += 2) {
			res.at<uchar>(i, j) = image.at<uchar>(i / 2, j / 2);
			res.at<uchar>(i, j + 1) = interpolate_bilinear(image, i / 2, j / 2);
		}
	}
	return res;
}
/**
	Apply a threshold filter with a value
	The last parameter determine if its a low or high threshold
*/
cv::Mat threshold(const cv::Mat& image, uchar value, bool high) {
	cv::Mat res = image.clone();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = res.at<uchar>(i, j);
			if (high) {
				if (oldValue > value) {
					res.at<uchar>(i, j) = 255;
				}
			}
			else {
				if (oldValue < value) {
					res.at<uchar>(i, j) = 0;
				}
			}
		}
	}

	return res;
}


/**
	Apply a combined threshold (low and high) which reduce the grey layers to 2
*/
cv::Mat thresholdC(const cv::Mat& image, uchar value) {
	cv::Mat res = image.clone();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = res.at<uchar>(i, j);
			if (oldValue > value) {
				res.at<uchar>(i, j) = 255;
			}

			if (oldValue < value) {
				res.at<uchar>(i, j) = 0;
			}
		}
	}
	return res;
}

/**
	Equalize the image uniformly with an affine function  
*/
cv::Mat normalize(const cv::Mat& image, uchar fMin, uchar fMax){
	
	uchar vMin;
	uchar vMax;
	evalMinMax(image, vMin, vMax);

	cv::Mat res = image.clone();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = res.at<uchar>(i, j);
			res.at<uchar>(i, j) = ((oldValue - fMin) * ((vMax - vMin) / (fMax - fMin))) + vMin;
		}
	}
	return res;
}

/**
	Reduce the grey layers in the image to x
*/
cv::Mat quantize(const cv::Mat& image, int layers) {
	cv::Mat res = image.clone();

	uchar unit = floor(255 / layers);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = res.at<uchar>(i, j);
			uchar interval = floor(oldValue / unit);

			res.at<uchar>(i, j) = unit * interval+floor(unit/2);
			
			//better render by giving extreme value to min and max
			if (interval == 0) {
				res.at<uchar>(i, j) = 0;
			}
			else if (interval == layers-1) {
				res.at<uchar>(i, j) = 255;
			}
		}
	}


	return res;
}

/***
	Equalize the image with a cumulated histogram technique
*/
cv::Mat equalize(const cv::Mat& image) {
	
	uchar vMin;
	uchar vMax;
	evalMinMax(image, vMin, vMax);

	cv::Mat res = image.clone();
	map<uchar, int> hist = histogram_cumul(image);

	int size = image.rows*image.cols;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar oldValue = res.at<uchar>(i, j);
			int histValue = hist[oldValue];

			uchar test = (vMax / size)*histValue + vMin;
			res.at<uchar>(i, j) = test;
		}
	}

	return res;
}

cv::Mat thresholdOtsu(const cv::Mat& image) {
	cv::Mat res = image.clone();
	//TODO 

	return res;
}

