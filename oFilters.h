#ifndef OFILTERS_H
#define OFILTERS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif



#endif // OFILTERS_H


/*
    Compute the convolution of a float image by kernel.
    Result has the same size as image.
    Pixel values outside of the image domain have a value of zero
*/
cv::Mat convolution(cv::Mat image, cv::Mat kernel)
{
    cv::Mat res = image.clone();
    float size = kernel.rows;

    /*
    cout << "execute " << endl;
    cout << "kernel cols="<< kernel.cols<<endl;
    cout << "kernel rows=" << kernel.rows<< endl;
    */

    for(int i = 0; i<image.rows; i++){
        for(int j = 0; j<image.cols; j++){

            float pixelValue = 0;

            for( int fx = 0; fx<size; fx++){
                for(int fy= 0; fy<size; fy++){

                    if(  ( (i+fx)>image.rows ) | ( (j+fy)>image.cols ) ){
                        pixelValue += 0;
                    }

                    else{
                        pixelValue+= image.at<float>((i+fx),(j+fy)) *  kernel.at<float>(fx,fy) ;
                    }
                }
            }
            res.at<float>(i,j) = pixelValue;

        }
    }
    std::cout << "end" << std::endl;
    return res;
}

/**
    Compute a mean filter of size 2k+1
    Pixel values outside of the image domain have a value of zero
*/
cv::Mat meanFilter(cv::Mat image, int size){
    cv::Mat res = image.clone();
    float count = (2*size +1)*(2*size+1);

    std::cout << "execute " << std::endl;

    for(int i = 0; i<image.rows; i++){
        for(int j = 0; j<image.cols; j++){

            float pixelValue = 0;

            for( int fx =(i-size);fx<=(i+size);fx++){
                for(int fy=(j-size) ; fy<=(j+size);fy++){
                    if((fx < 0)||(fy<0)||(fx>image.rows-1)||(fy>image.cols-1)){
                        pixelValue += 0;
                    }
                    else{
                        pixelValue+= image.at<float>(fx,fy);
                    }
                }
            }
            res.at<float>(i,j) = pixelValue/count;
        }
    }
    std::cout << "end" << std::endl;
    return res;

}

/**
    Compute the sum of absolute partial derivative according to Sobel's method
*/
cv::Mat edgeSobel(cv::Mat image)
{
    cv::Mat res = image.clone();

    cv::Mat gx = (cv::Mat_<float>(3,3) << -1,0,1,-2,0,2,-1,0,1);
    cv::Mat gy = (cv::Mat_<float>(3,3) << 1,2,1,0,0,0,-1,-2,-1);

    cv::Mat x = convolution(image, gx);
    cv::Mat y = convolution(image, gy);

    res = abs(x)+abs(y);
    //res = normalize(res, 0.0, 1.0);


    return res;
}

float gaussian(float x, float sigma2)
{
    return 1.0/(2*M_PI*sigma2)*exp(-x*x/(2*sigma2));
}

/*
    TODO @todo
    Performs a bilateral filter with the given spatial smoothing kernel
    and a intensity smoothing of scale sigma_r.

*/

cv::Mat bilateralFilter(cv::Mat image, cv::Mat kernel, double sigma_r)
{
    cv::Mat res = image.clone();
    /********************************************
                YOUR CODE HERE
    *********************************************/

    /********************************************
                END OF YOUR CODE
    *********************************************/
    return res;
}
