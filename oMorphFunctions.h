#ifndef OMORPHFUNCTIONS_H
#define OMORPHFUNCTIONS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif // OMORPHFUNCTIONS_H

cv::Mat erode(cv::Mat image, cv::Mat structuringElement);
cv::Mat dilate(cv::Mat image, cv::Mat structuringElement);
cv::Mat open(cv::Mat image, cv::Mat structuringElement);
cv::Mat close(cv::Mat image, cv::Mat structuringElement);
cv::Mat hitOrMissTransform(cv::Mat image, cv::Mat structuringElementObject, cv::Mat structuringElementBackground);


/*
    Pixel outside the image have value 1
*/
cv::Mat erode(cv::Mat image, cv::Mat structuringElement)
{
    cv::Mat res = image.clone();

    float structWidth = (structuringElement.rows)/2;
    float structHeight = (structuringElement.rows)/2;

    for(int i = 0; i<res.rows; i++){
        for(int j = 0; j<res.cols; j++){

            std::vector<float> pixels;
            bool eroded = false;


            for(int fx = (-structHeight/2) ; fx<(structHeight/2); fx++){
                for(int fy = (-structWidth/2); fy<(structWidth/2); fy++){

                    if(  ((i+fx)>0) && ((i+fx)<image.rows) && ((j+fy)>0) &&  ((j+fy)<image.cols)   ){

                        //position on the structuring elements
                        int cursX = fx + structHeight/2;
                        int cursY = fy +  structWidth/2;
                        if(image.at<float>(i+fx, j+fy) != 1 && structuringElement.at<float>(cursX,cursY)==1){
                           eroded = true;
                        }

                    }
                    else{
                        eroded  = true;
                    }

                }
            }
            //erode
            if(eroded){
                res.at<float>(i, j) = 0; // <--
                //cout<<"eroded"<<endl;

            }
            else{
                res.at<float>(i,j) = 1;
                //cout<<"not eroded"<<endl;

            }

        }
    }

    return res;
}

/*
     Pixel outside the image have value 0
*/
cv::Mat dilate(cv::Mat image, cv::Mat structuringElement)
{
    cv::Mat res = image.clone();

    float structWidth = (structuringElement.cols)/2;
    float structHeight = (structuringElement.rows)/2;


    //cout<<"width"<< structuringElement.rows << endl;
    //cout << "height"<< structuringElement.cols << endl;

    for(int i = 0; i<res.rows; i++){
        for(int j = 0; j<res.cols; j++){

            for(int fx = (-structHeight/2) ; fx<(structHeight/2); fx++){
                for(int fy = (-structWidth/2); fy<(structWidth/2); fy++){


                    if(  ((i+fx)>0) && ((i+fx)<image.rows) && ((j+fy)>0) &&  ((j+fy)<image.cols)   ){

                        //position on the structuring elements
                        res.at<float>(i+fx,j+fy) = 1;

                    }
                    else{
                        res.at<float>(i+fx, j+fy) = 0;
                    }

                }
            }


        }
    }

    return res;
}

cv::Mat open(cv::Mat image, cv::Mat structuringElement)
{

    cv::Mat res = cv::Mat::zeros(1,1,CV_32FC1);

    res = erode(image, structuringElement);
    res = dilate(res, structuringElement);

    return res;
}


cv::Mat close(cv::Mat image, cv::Mat structuringElement)
{

    cv::Mat res = cv::Mat::zeros(1,1,CV_32FC1);

    res = dilate(image, structuringElement);
    res = erode(res, structuringElement);

    return res;
}

/* TODO @todo */
cv::Mat hitOrMissTransform(cv::Mat image, cv::Mat structuringElementObject, cv::Mat structuringElementBackground)
{
    cv::Mat res = cv::Mat::zeros(1,1,CV_32FC1);

    return res;
}
