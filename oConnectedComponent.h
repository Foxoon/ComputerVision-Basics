#ifndef OCONNECTEDCOMPONENT_H
#define OCONNECTEDCOMPONENT_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <stack>
#include <list>
#include <iostream>
#endif // OCONNECTEDCOMPONENT_H

cv::Mat ccLabel(cv::Mat image);
cv::Mat ccAreaFilter(cv::Mat image, int size);


/* refactor @todo */


/**
    Performs a labeling of image connected component with 4 connectivity
    with a depth-first exploration.
    Any non zero pixel of the image is considered as present.
*/
cv::Mat ccLabel(cv::Mat image)
{
    cv::Mat res = cv::Mat::zeros(image.rows, image.cols, CV_32SC1); // 32 int image

    typedef struct {
        int x;
        int y;
    }Coord;

    int countComponents = 1;

    for(int i=0; i<res.rows; i++){
        for(int j=0; j<res.cols; j++){

            int pixelValue = image.at<float>(i, j);
            int pixelComponent = res.at<int>(i,j);

            //compoment
            if(pixelValue == 1.0 && pixelComponent==0){
                std::stack<Coord> s;
                Coord c {i,j};

                s.push(c);

                while(!s.empty()){
                    Coord ref = s.top();
                    s.pop();



                    int pixelValueTMP = image.at<float>(ref.x,ref.y);
                    int pixelComponentTMP = res.at<int>(ref.x,ref.y);
                    if(pixelValueTMP == 1.0 && pixelComponentTMP==0){
                        std::cout << "x = " << ref.x << " , y = " << ref.y << std::endl;
                        res.at<int>(ref.x,ref.y)= countComponents;

                        //left
                        if( (ref.x -1 ) >= 0 ){
                            Coord l {ref.x -1, ref.y};
                            s.push(l);
                            //cout << "left" << endl;
                        }

                        //right
                        if( (ref.x +1 ) < res.rows ){
                            Coord r {ref.x+1, ref.y};
                            s.push(r);
                        }

                        //top
                        if( (ref.y -1 ) >= 0 ){
                            Coord t {ref.x, ref.y -1};
                            s.push(t);
                        }

                        //bottom
                        if( (ref.y +1 ) < res.cols ){
                            Coord b {ref.x, ref.y+1};
                            s.push(b);
                        }

                    }

                }
             countComponents++;

            }
        }
    }
    return res;
}

/**
    Deletes the connected components (4 connectivity) containing less than size pixels.
*/
cv::Mat ccAreaFilter(cv::Mat image, int size)
{
   cv::Mat res = cv::Mat::zeros(image.rows, image.cols, image.type());
    assert(size>0);

    typedef struct {
        int x;
        int y;
    }Coord;

    int countComponents = 1;
    for(int i=0; i<res.rows; i++){
        for(int j=0; j<res.cols; j++){

            int pixelValue = image.at<float>(i, j);
            int pixelComponent = res.at<int>(i,j);

            //compoment
            if(pixelValue == 1.0 && pixelComponent==0){
                std::stack<Coord> s;
                Coord c {i,j};
                s.push(c);

                int countNbPixelPerLabel = 0;
                std::list<Coord> labelPixels;

                while(!s.empty()){
                    Coord ref = s.top();
                    s.pop();

                    int pixelValueTMP = image.at<float>(ref.x,ref.y);
                    int pixelComponentTMP = res.at<int>(ref.x,ref.y);
                    if(pixelValueTMP == 1.0 && pixelComponentTMP==0){
                        std::cout << "x = " << ref.x << " , y = " << ref.y << std::endl;
                        res.at<int>(ref.x,ref.y)= countComponents;

                        //left
                        if( (ref.x -1 ) >= 0 ){
                            Coord l {ref.x -1, ref.y};
                            s.push(l);
                            //cout << "left" << endl;
                        }

                        //right
                        if( (ref.x +1 ) < res.rows ){
                            Coord r {ref.x+1, ref.y};
                            s.push(r);
                        }

                        //top
                        if( (ref.y -1 ) >= 0 ){
                            Coord t {ref.x, ref.y -1};
                            s.push(t);
                        }

                        //bottom
                        if( (ref.y +1 ) < res.cols ){
                            Coord b {ref.x, ref.y+1};
                            s.push(b);
                        }


                        labelPixels.push_back(ref);
                        countNbPixelPerLabel++;
                    }

                }


                if(countNbPixelPerLabel >= size){
                    countComponents ++;
                }
                else{
                    for(std::list<Coord>::iterator it = labelPixels.begin(); it != labelPixels.end(); it++ ){
                        res.at<int>(it->x, it->y) = 0;
                    }
                }
            }
        }
    }
    cv::Mat resp = image.clone();
    for(int i = 0; i<res.rows; i++){
        for(int j = 0; j<res.cols; j++){
            if(res.at<int>(i,j) == 0){
                resp.at<float>(i,j) = 0.0;
            }
        }
    }
    return resp;

}
