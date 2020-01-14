// ConsoleOpenCV-Try2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<opencv2/opencv.hpp>
#include<iostream>
#include "Classes/Editing.h"
using namespace std;

int main()
{
	cv::Mat img = cv::imread("Ressources/poor.png", false);

	cv::namedWindow("input", cv::WINDOW_NORMAL);
	imshow("input",img);

	cv::Mat fimg = cv::imread("Ressources/poor.png", false);
	cv::Mat out2 = quantize(fimg,4);
	
	map<uchar, int> m = histogram_cumul(fimg);
	show_histogram(m);


	cv::namedWindow("output", cv::WINDOW_NORMAL);
	imshow("output", out2);

	cv::waitKey(0);
	return 0;
}

